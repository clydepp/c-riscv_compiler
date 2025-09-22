#include "ast_default.hpp"

namespace ast{
void Default::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const{
    std::string default_label = context.GetUniqueLabel("default");

    stream << default_label << ":" << std::endl;
    statement_->EmitRISC(stream, reg, context);
    stream << "\tj " << context.GetSwitchEndLabel() << std::endl;
}

void Default::Print(std::ostream& stream) const{
    stream << "\tdefault: ";
    statement_->Print(stream);
    stream << std::endl;
}
}
