#include "ast_init_declarator.hpp"

namespace ast {

void InitDeclarator::EmitRISC(std::ostream& stream, std::string&, Context& context) const
{

    std::string ret_reg = context.GetFreeRegister(); // this gets a free register that we can use for this variable
    IdentifierCase ident_check = context.GetIdentifierType();
    if (ident_check != IdentifierCase::DECL) {

        std::cout << "ret_reg is " << ret_reg << std::endl;

        // IdentifierCase ident_fetch = context.GetIdentifierType();

        if (initializer_)
            initializer_->EmitRISC(stream, ret_reg, context);

        std::string ident_case = "local_init";
        context.SetIdentifierType(ident_case);
    }
    declarator_->EmitRISC(stream, ret_reg, context);

    context.DeallocateRegister(ret_reg);
}

void InitDeclarator::Print(std::ostream& stream) const
{
    declarator_->Print(stream);
    if (initializer_){
        stream << " = ";
        initializer_->Print(stream);
    }
}

}
