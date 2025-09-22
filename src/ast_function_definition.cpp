#include "ast_function_definition.hpp"

namespace ast {

void FunctionDefinition::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    // Emit assembler directives.
    // TODO: these are just examples ones, make sure you understand
    // the concept of directives and correct them.

    std::string ident_case = "funct";
    context.SetIdentifierType(ident_case);

    std::string printcase1 = "identi";
    std::string printcase2 = "params";
    stream << ".text" << std::endl;
    stream << ".globl ";
    declarator_->EmitRISC(stream, printcase1, context);
    stream << std::endl;

    printcase1 = "identi1";
    declarator_->EmitRISC(stream, printcase1, context);

    declarator_->EmitRISC(stream, printcase2, context); // prints the function header (i.e. f:)
    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, reg, context);
        std::cout << "gone into compound statement" << std::endl;
    }
    else {
        std::cout << "no compound statement" << std::endl;
    }
    // stream << "\tmv a0, a5" << std::endl; (this should be streamed after each function)
    if (context.CheckGlobalEnd()){
        stream << "global_end";
        stream << context.GetFunctionName() << ":" << std::endl;
    }
    context.EndStack(stream);
}

void FunctionDefinition::Print(std::ostream& stream) const
{
    stream << declaration_specifiers_ << " ";

    declarator_->Print(stream);
    stream << "() {" << std::endl;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->Print(stream);
    }
    stream << "}" << std::endl;
}

}
