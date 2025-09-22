#include "ast_context.hpp"
#include "ast_while.hpp"

namespace ast {


void While::EmitRISC(std::ostream& stream, std::string& , Context& context) const {
    std::string start_label = context.MakeLabel("while_start");// to implement in context
    std::string end_label = context.MakeLabel("while_end");

    stream << start_label << ":" << std::endl;

    std::string cond_reg = context.GetFreeRegister();
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);

    condition_->EmitRISC(stream, cond_reg, context);
    stream << "\tbeq " << cond_reg << ", zero, " << end_label << std::endl;

    if (body_ != nullptr) body_->EmitRISC(stream, cond_reg, context);
    stream << "\tj " << start_label << std::endl; 

    stream << end_label << ":" << std::endl;

    context.DeallocateRegister(cond_reg);
}

void While::Print(std::ostream& stream) const {
    stream << "while (";
    condition_->Print(stream);
    stream << ") {" << std::endl;
    if (body_ != nullptr) body_->Print(stream);
    stream << "}" << std::endl;
}

} // namespace ast
