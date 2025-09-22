#include "ast_assignment.hpp"

namespace ast {
void Assignment::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{

    reg = context.GetFreeRegister();
    std::string reg2 = context.GetFreeRegister();

    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    assign_ex_->EmitRISC(stream, reg, context); // lw


    if (assign_ex_){
        ident_case = "local_overwrite";
        context.SetIdentifierType(ident_case);
        unary_ex_->EmitRISC(stream, reg, context); // prints store word (sw)
    }

    context.DeallocateRegister(reg);
    context.DeallocateRegister(reg2);
}
void Assignment::Print(std::ostream& stream) const
{
    unary_ex_->Print(stream);
    stream << " = ";
    assign_ex_->Print(stream);
    stream << ";\n";
}
}
