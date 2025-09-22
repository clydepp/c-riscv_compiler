#include "ast_jump_statement.hpp"

namespace ast {

void ReturnStatement::EmitRISC(std::ostream& stream, std::string&, Context& context) const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);

    context.SetGlobalEndLabel();
    std::string ret_reg = context.GetFreeRegister();
    if (expression_ != nullptr)
    {
        expression_->EmitRISC(stream, ret_reg, context);
    }
    std::cout << "return register:" << ret_reg << std::endl;
    stream << "\tmv a0, " << ret_reg << std::endl;
    stream << "\tj global_end";
    stream << context.GetFunctionName() <<std::endl;
    // stream << "jump" << std::endl;
}

void ReturnStatement::Print(std::ostream& stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

}
