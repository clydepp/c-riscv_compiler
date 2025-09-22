#include "ast_ifelse.hpp"

namespace ast {
void IfElse::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{
    // if (condition) { true } else { false }
    // condition is a boolean expression
    // true and false are statements

    std::string cond_reg = context.GetFreeRegister();
    std::string else_label = context.MakeLabel("else"); // something like L1
    std::string end_label = context.MakeLabel("end"); // something like L2
    // std::string if_label = context.MakeLabel("if");

    condition_->EmitRISC(stream, cond_reg, context);
    if (else_body_) {
        stream << "\tbeq " << cond_reg << ", zero, " << else_label << std::endl;
    }
    else {
        stream << "\tbeq " << cond_reg << ", zero, " << end_label << std::endl;
    }

    context.DeallocateRegister(cond_reg);

    if_body_->EmitRISC(stream, reg, context);

    if (context.CheckGlobalEnd()){
        stream << "\tj global_end";
        stream << context.GetFunctionName() <<std::endl;
    }
    else
        stream << "\tj " << end_label << std::endl;

    if (else_body_){
        stream << else_label << ":" << std::endl;
        else_body_->EmitRISC(stream, reg, context);
    }

    stream << end_label << ":"<< std::endl;

}

void IfElse::Print(std::ostream& stream) const
{

    stream << "if (";
    condition_->Print(stream);
    stream << ") {\n" ;
    if_body_->Print(stream);
    stream << "} else {\n";
    if (else_body_)
        else_body_->Print(stream);
    stream << "}";
    // do this later

}

}
