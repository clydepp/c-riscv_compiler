#include "ast_increment.hpp"

namespace ast {

void RightIncrement::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);

    std::string ret_reg = context.GetFreeRegister();
    postfix_expression_->EmitRISC(stream, ret_reg, context);

    if (incr_operator_ == IncrementOper::INC_OP)
        stream << "addi " << reg << ", " << ret_reg << ", 1" << std::endl;
    else
        stream << "addi " << reg << ", " << ret_reg << ", -1" << std::endl;

    context.DeallocateRegister(ret_reg);

}

void RightIncrement::Print(std::ostream& stream) const{
    postfix_expression_->Print(stream);
    stream << "++" << std::endl;
}

void LeftIncrement::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);

    std::string ret_reg = context.GetFreeRegister();
    unary_expression_->EmitRISC(stream, ret_reg, context);

    if (incr_operator_ == IncrementOper::INC_OP)
        stream << "addi " << reg << ", " << ret_reg << ", 1" << std::endl;
    else
        stream << "addi " << reg << ", " << ret_reg << ", -1" << std::endl;

    context.DeallocateRegister(ret_reg);
}

void LeftIncrement::Print(std::ostream& stream) const {
    stream << "++";
    unary_expression_->Print(stream);
}

}
