#include "ast_declaration.hpp"

namespace ast {

void Declaration::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{
    /*std::string ident_case = "global_decl";
    context.SetIdentifierType(ident_case);
    std::cout << "global declaration" << std::endl;*/

    init_decl_list_->EmitRISC(stream, reg, context);
}

void Declaration::Print(std::ostream& stream) const
{
    stream << "Declaration: ";
    init_decl_list_->Print(stream);
    stream << std::endl;
}

}

