#include "ast_function_call.hpp"

namespace ast {

void FunctionCall::EmitRISC(std::ostream &stream, std::string& reg, Context& context) const {
    // clear all registers and use a0 -> onwards
    // make new context reg.
    context.IsFunctionCall(true);
    context.ResetArgumentRegisters();

    if (argument_expression_list_)
        argument_expression_list_->EmitRISC(stream, reg, context);

    context.ResetArgumentRegisters();

    std::string ident_case = "funct";
    context.SetIdentifierType(ident_case);
    stream << "\tcall ";
    function_name_->EmitRISC(stream, reg, context);
    stream << std::endl;
    stream << "\tmv " << reg << ", a0" << std::endl;
    context.IsFunctionCall(false);
}

void FunctionCall::Print(std::ostream &stream) const {
    function_name_->Print(stream);
    stream << std::endl;
    if (argument_expression_list_)
        argument_expression_list_->Print(stream);
}

}
