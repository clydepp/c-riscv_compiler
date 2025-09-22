#include "ast_relationalop.hpp"

namespace ast {
void LessThan::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tslt " << reg << ", " << reg << ", " << reg2 << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void LessThan::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<";
    GetRight()->Print(stream);
    stream << '\n';
}

void LessThanEq::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsgt " << reg << ", " << reg << ", " << reg2 << std::endl;
    stream << "\txori " << reg << ", " << reg << ", 1" << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void LessThanEq::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "<=";
    GetRight()->Print(stream);
    stream << '\n';
}

void GreaterThan::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsgt " << reg << ", " << reg << ", " << reg2 << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void GreaterThan::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << ">";
    GetRight()->Print(stream);
    stream << '\n';
}

void GreaterThanEq::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tslt " << reg << ", " << reg << ", " << reg2 << std::endl;
    stream << "\txori " << reg << ", " << reg << ", 1" << std::endl;
    stream << "\tandi " << reg << ", " << reg << ", 0xff" << std::endl;

    context.DeallocateRegister(reg2);
}

void GreaterThanEq::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << ">=";
    GetRight()->Print(stream);
    stream << '\n';
}
}
