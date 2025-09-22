#include "ast_direct_declarator.hpp"

namespace ast {

// only called for function declarations, not for variable declarations
void DirectDeclarator::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{
    IdentifierCase id_type = context.GetIdentifierType();
    switch (id_type){
        case IdentifierCase::FUNCT:
            if (reg == "identi"){
                identifier_->EmitRISC(stream, reg, context);
            }
            else if (reg == "identi1"){
                identifier_->EmitRISC(stream, reg, context);
                stream << ":" << std::endl;
                context.InitializeStack(stream);
            }
            else if (reg == "params"){
                if (parameters_){
                    parameters_->EmitRISC(stream, reg, context);
                    context.ResetArgumentRegisters(); // to avoid no space throw
                }
            }
            break;
        case IdentifierCase::DECL:
            std::cout << "function declaration (no compound statement body)" << std::endl;
            identifier_->EmitRISC(stream, reg, context);
            break;
        case IdentifierCase::LOCAL_INIT:
            identifier_->EmitRISC(stream, reg, context);
            break;
        case IdentifierCase::LOCAL_OPER:
            identifier_->EmitRISC(stream, reg, context);
            break;
        case IdentifierCase::LOCAL_OVERWRITE:
            identifier_->EmitRISC(stream, reg, context);
            break;
        default:
            throw std::runtime_error("Invalid identifier case");
    }

}

void DirectDeclarator::Print(std::ostream& stream) const
{
    identifier_->Print(stream);
}

} // namespace ast
