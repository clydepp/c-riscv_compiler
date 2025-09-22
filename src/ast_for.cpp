#include "ast_context.hpp"
#include "ast_for.hpp"


namespace ast {
void For::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    std::string start_label = context.MakeLabel("for_start");
    std::string end_label = context.MakeLabel("for_end");

    initialization_->EmitRISC(stream, reg, context);
    stream << start_label << ":" << std::endl;

    std::string cond_reg = context.GetFreeRegister();
    condition_->EmitRISC(stream, cond_reg, context);
    stream << "\tbeq " << cond_reg << ", zero, " << end_label << std::endl;

    body_->EmitRISC(stream, cond_reg, context);

    increment_->EmitRISC(stream, reg, context);
    stream << "\tj " << start_label << std::endl;
    stream << end_label << ":" << std::endl;

    context.DeallocateRegister(cond_reg);
}

void For::Print(std::ostream& stream) const {
    stream << "for (";
    initialization_->Print(stream);
    stream << "; ";
    condition_->Print(stream);
    stream << "; ";
    increment_->Print(stream);
    stream << ") {" << std::endl;
    body_->Print(stream);
    stream << "}" << std::endl;
}

} // namespace ast
