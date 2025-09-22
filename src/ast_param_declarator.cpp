#include "ast_param_declarator.hpp"

namespace ast {
void ParamDeclaration::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const {
    std::string ident_case = "local_init";
    context.SetIdentifierType(ident_case);
    reg = context.GetFreeRegister();
    declarator_->EmitRISC(stream, reg, context);

}

void ParamDeclaration::Print(std::ostream& stream) const {
    declarator_->Print(stream);
    stream << ", " << std::endl;
}

}
