#include "ast_shifts.hpp"

namespace ast {
void ShiftLeft::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsll " << reg << ", " << reg << ", " << reg2 << std::endl;

    context.DeallocateRegister(reg2);
}

void ShiftLeft::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<<";
    GetRight()->Print(stream);
    stream << '\n';
}

void ShiftRight::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsra " << reg << ", " << reg << ", " << reg2 << std::endl;

    context.DeallocateRegister(reg2);
}

void ShiftRight::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<<";
    GetRight()->Print(stream);
    stream << '\n';
}
}
