#include "ast_equalityop.hpp"

namespace ast {
void EqualOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsub " << reg << ", " << reg << ", " << reg2 << std::endl; // x-y
    stream << "\tseqz " << reg << ", " << reg << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void EqualOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<";
    GetRight()->Print(stream);
    stream << '\n';
}

void NotEqualOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsub " << reg << ", " << reg << ", " << reg2 << std::endl; // x-y
    stream << "\tsnez " << reg << ", " << reg << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void NotEqualOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<";
    GetRight()->Print(stream);
    stream << '\n';
}
}
