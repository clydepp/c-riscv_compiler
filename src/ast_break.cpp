#include "ast_break.hpp"

namespace ast {
void BreakStatement::EmitRISC(std::ostream& stream, std::string& , Context& context) const {
    stream << "\tj " << context.GetCurrentBreakLabel() << std::endl;
}

void BreakStatement::Print(std::ostream& stream) const {
    stream << "break;";
}
}
