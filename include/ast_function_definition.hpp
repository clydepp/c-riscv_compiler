#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_identifier_case.hpp"
namespace ast {

class FunctionDefinition : public Node
{
private:
    const TypeSpecifier declaration_specifiers_; // Function TYPE
    NodePtr declarator_; // Function NAME
    NodePtr compound_statement_; // Function BODY

public:
    FunctionDefinition(TypeSpecifier declaration_specifiers, NodePtr declarator, NodePtr compound_statement) : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)), compound_statement_(std::move(compound_statement)){};

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
