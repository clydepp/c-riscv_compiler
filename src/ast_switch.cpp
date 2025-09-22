#include "ast_switch.hpp"

namespace ast{
void SwitchStatement::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const{
    std::string end_label = context.MakeLabel("switch_end");
    std::string cond_reg = context.GetFreeRegister();
    expression_->EmitRISC(stream, cond_reg, context); // lw reg (this is the comparison register)
    
    // this label needs to be passed into statement somehow?
    context.PushBreakLabel(end_label);

    context.SetSwitchCondition(cond_reg);
    context.SetSwitchEndLabel(end_label);

    statement_->EmitRISC(stream,reg,context);
    stream << end_label << ":" << std::endl;

    context.PopBreakLabel();
    context.DeallocateRegister(cond_reg);

}

void SwitchStatement::Print(std::ostream& stream) const{
    stream << "\tswitch ( ";
    expression_->Print(stream);
    stream << " )" << std::endl;
    stream << "\t{"<< std::endl;
    statement_->Print(stream);
    stream << "}" << std::endl;

}
}
