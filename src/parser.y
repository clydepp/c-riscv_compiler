// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires {
	#include "ast.hpp"
	using namespace ast;

	extern int yylineno;
	extern char* yytext;
	extern Node* g_root;
	extern FILE* yyin;

	int yylex(void);
	void yyerror(const char*);
	int yylex_destroy(void);
}

%define parse.error detailed
%define parse.lac full

// Represents the value associated with any kind of AST node.
%union {
  Node*        	node;
  NodeList*    	node_list;
  int          	number_int;
  double       	number_float;
  std::string* 	string; // IDENTIFER
  TypeSpecifier	type_specifier;
  yytokentype  	token;
  IdentifierCase identifier_case;
  IncrementOper increment_oper;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token UNKNOWN
%token <increment_oper> INC_OP DEC_OP

%type <node> external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration  // declaration_specifiers
%type <node> init_declarator struct_specifier struct_declaration //  type_specifier
%type <node> struct_declarator enum_specifier enumerator declarator direct_declarator pointer parameter_declaration
%type <node> type_name abstract_declarator direct_abstract_declarator initializer statement labeled_statement
%type <node> compound_statement expression_statement selection_statement iteration_statement jump_statement init_declarator_list

%type <node_list> statement_list declaration_list struct_declaration_list initializer_list
%type <node_list> struct_declarator_list parameter_list
%type <node_list> enumerator_list identifier_list argument_expression_list translation_unit

%type <string> unary_operator assignment_operator storage_class_specifier

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <string> IDENTIFIER
%type <type_specifier> type_specifier declaration_specifiers specifier_qualifier_list


%start ROOT
%%

ROOT
  : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = new NodeList(NodePtr($1)); }
	| translation_unit external_declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	;

external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1; }
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement { $$ = new FunctionDefinition($1, NodePtr($2), NodePtr($3)); }
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;


primary_expression
	: IDENTIFIER { $$ = new Identifier(std::move(*$1)); delete $1; }
	| INT_CONSTANT { $$ = new IntConstant($1); }
    | FLOAT_CONSTANT
	| STRING_LITERAL
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']' { $$ = new ArrayAccess(NodePtr($1), NodePtr($3)); }
	| postfix_expression '(' ')' { $$ = new FunctionCall(NodePtr($1), nullptr); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new FunctionCall(NodePtr($1), $3); }
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP { $$ = new RightIncrement(NodePtr($1), $2); }
	| postfix_expression DEC_OP { $$ = new RightIncrement(NodePtr($1), $2); }
	;

argument_expression_list
	: assignment_expression { $$ = new ArgumentList(NodePtr($1)); }
	| argument_expression_list ',' assignment_expression { $1->PushBack(NodePtr($3)); $$=$1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression { $$ = new LeftIncrement(NodePtr($2), $1); }
	| DEC_OP unary_expression { $$ = new LeftIncrement(NodePtr($2), $1); }
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new MulOp(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '/' cast_expression { $$ = new DivOp(NodePtr($1), NodePtr($3)); }
	| multiplicative_expression '%' cast_expression { $$ = new ModOp(NodePtr($1), NodePtr($3)); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new AddOp(NodePtr($1), NodePtr($3)); }
	| additive_expression '-' multiplicative_expression { $$ = new SubOp(NodePtr($1), NodePtr($3)); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new ShiftLeft(NodePtr($1), NodePtr($3)); }
	| shift_expression RIGHT_OP additive_expression { $$ = new ShiftRight(NodePtr($1), NodePtr($3)); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression { $$ = new LessThan(NodePtr($1), NodePtr($3)); }
	| relational_expression '>' shift_expression  { $$ = new GreaterThan(NodePtr($1), NodePtr($3)); }
	| relational_expression LE_OP shift_expression { $$ = new LessThanEq(NodePtr($1), NodePtr($3)); }
	| relational_expression GE_OP shift_expression { $$ = new GreaterThanEq(NodePtr($1), NodePtr($3)); }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQ_OP relational_expression { $$ = new EqualOp(NodePtr($1), NodePtr($3)); }
	| equality_expression NE_OP relational_expression { $$ = new NotEqualOp(NodePtr($1), NodePtr($3)); }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression { $$ = new BitwAndOp(NodePtr($1), NodePtr($3)); }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression { $$ = new XorOp(NodePtr($1), NodePtr($3)); }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression { $$ = new BitwOrOp(NodePtr($1), NodePtr($3)); }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new AndOp(NodePtr($1), NodePtr($3)); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression  { $$ = new OrOp(NodePtr($1), NodePtr($3)); }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression { $$ = new TernaryOp(NodePtr($1), NodePtr($3), NodePtr($5)); }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression {$$ = new Assignment(NodePtr($1), NodePtr($3)); }
	;

assignment_operator
	: '=' // { $$ = }
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';' // type declaration lol
	| declaration_specifiers init_declarator_list ';' { $$ = new Declaration($1, NodePtr($2)); }

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers
    | type_specifier '[' constant_expression ']'
    | type_specifier '[' ']'
	;

init_declarator_list
	: init_declarator { $$ = $1; }
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator { $$ = new InitDeclarator(NodePtr($1), NULL); }
	| declarator '=' initializer { $$ = new InitDeclarator(NodePtr($1), NodePtr($3)); }
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID { $$ = TypeSpecifier::VOID; }
	| CHAR { $$ = TypeSpecifier::CHAR; }
	| SHORT { $$ = TypeSpecifier::SHORT; }
	| INT { $$ = TypeSpecifier::INT; }
	| LONG { $$ = TypeSpecifier::LONG; }
	| FLOAT { $$ = TypeSpecifier::FLOAT; }
	| DOUBLE { $$ = TypeSpecifier::DOUBLE; }
	| SIGNED
	| UNSIGNED
    | struct_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration { $$ = new NodeList(NodePtr($1)); }
	| struct_declaration_list struct_declaration { $1->PushBack(NodePtr($2)); $$=$1; }
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

declarator
	: pointer direct_declarator
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER {
		$$ = new Identifier(std::move(*$1)); // this moves the value of the string as a parameter for the constructor
		delete $1;
	}
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']' { $$ = new Array(NodePtr($1), NodePtr($3)); }
	| direct_declarator '[' ']' { $$ = new Array(NodePtr($1), nullptr); }
	| direct_declarator '(' parameter_list ')' { $$ = new DirectDeclarator(NodePtr($1), $3); } // has parameters in function call
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')' { $$ = new DirectDeclarator(NodePtr($1), nullptr); } // empty function call
	;

pointer
	: '*'
	| '*' pointer
	;

parameter_list
	: parameter_declaration { $$ = new NodeList(NodePtr($1)); }
	| parameter_list ',' parameter_declaration { $1->PushBack(NodePtr($3)); $$=$1; }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new ParamDeclaration($1, NodePtr($2)); }
	| declaration_specifiers abstract_declarator
	| declaration_specifiers // let's not implement this for now
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement { $$ = $1; } // this is for switch case
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement { $$ = $1;}
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement { $$ = new Case(NodePtr($2), NodePtr($4)); }
	| DEFAULT ':' statement { $$ = new Default(NodePtr($3)); }
	;

compound_statement
	: '{' '}' { $$ = new CompoundStatement(nullptr, nullptr); }
	| '{' statement_list '}' { $$ = new CompoundStatement(nullptr, $2); }
	| '{' declaration_list '}' { $$ = new CompoundStatement($2, nullptr); } // only use is within its own local scope
	| '{' declaration_list statement_list '}'  { $$ = new CompoundStatement($2, $3); }
	;

declaration_list
	: declaration { $$ = new NodeList(NodePtr($1)); }
	| declaration_list declaration { $1->PushBack(NodePtr($2)); $$=$1; } // pass pointer to declaration_list
	;

statement_list
	: statement { $$ = new NodeList(NodePtr($1)); }
	| statement_list statement { $1->PushBack(NodePtr($2)); $$=$1; }
	;

expression_statement
	: ';'
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = new IfElse(NodePtr($3), NodePtr($5)); }
	| IF '(' expression ')' statement ELSE statement { $$ = new IfElse(NodePtr($3), NodePtr($5), NodePtr($7)); }
	| SWITCH '(' expression ')' statement { $$ = new SwitchStatement(NodePtr($3), NodePtr($5)); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new While(NodePtr($3), NodePtr($5)); }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement {$$ = new For(NodePtr($3), NodePtr($4), nullptr, NodePtr($6)); }
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = new For(NodePtr($3), NodePtr($4), NodePtr($5), NodePtr($7)); }
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';' { $$ = new BreakStatement(); }
	| RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement(NodePtr($2));
	}
	;



%%

void yyerror (const char *s)
{
  std::cerr << "Error: " << s << " at line " << yylineno;
  std::cerr << " near '" << yytext << "'" << std::endl;
  std::exit(1);
}

Node* g_root;

NodePtr ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if (yyin == nullptr) {
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    std::exit(1);
  }

  g_root = nullptr;
  yyparse();

  fclose(yyin);
  yylex_destroy();

  return NodePtr(g_root);
}
