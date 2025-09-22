#include "ast_operators.hpp"

namespace ast {

void Operator::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{

    GetLeft()->EmitRISC(stream, reg, context);
    GetRight()->EmitRISC(stream, reg, context);
}

void Operator::Print(std::ostream& stream) const
{
    GetLeft()->Print(stream);
    stream << " ";
    GetRight()->Print(stream);
}

void AddOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    std::cout << "allocated register" << reg2 << std::endl;
    context.PrintArgRegisters();

    GetLeft()->EmitRISC(stream, reg2, context); // destination
    if (reg == reg2){
        std::string reg3 = context.GetFreeRegister();
        GetRight()->EmitRISC(stream, reg3, context); // other param
        stream << "\tadd " << reg << ", " << reg << ", " << reg3 << std::endl;
    }
    else {
        GetRight()->EmitRISC(stream, reg, context); // other param
        stream << "\tadd " << reg << ", " << reg << ", " << reg2 << std::endl;
    }

    // context.DeallocateRegister(reg);
    context.DeallocateRegister(reg2);
}

void AddOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "+";
    GetRight()->Print(stream);
    stream << '\n';
}

void SubOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tsub " << reg << ", " << reg << ", " << reg2 << std::endl;

    context.DeallocateRegister(reg2);
}

void SubOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "-";
    GetRight()->Print(stream);
    stream << '\n';
}

void MulOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tmul " << reg << ", " << reg << ", " << reg2 << std::endl;

    context.DeallocateRegister(reg2);
}

void MulOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "*";
    GetRight()->Print(stream);
    stream << '\n';
}

void DivOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();

    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tdiv " << reg << ", " << reg << ", " << reg2 << std::endl;
    context.DeallocateRegister(reg2);
}

void DivOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "/";
    GetRight()->Print(stream);
    stream << '\n';
}


void BitwAndOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{


    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();


    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param


    stream << "\tand " << reg << ", " << reg << ", " << reg2 << std::endl;
    context.DeallocateRegister(reg2);
}


void BitwAndOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "&";
    GetRight()->Print(stream);
    stream << '\n';
}

void ModOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{


    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();


    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param


    stream << "\tmod " << reg << ", " << reg << ", " << reg2 << std::endl;
    context.DeallocateRegister(reg2);
}


void ModOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "%";
    GetRight()->Print(stream);
    stream << '\n';
}


void XorOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{


    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();


    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param


    stream << "\txor " << reg << ", " << reg << ", " << reg2 << std::endl;
    context.DeallocateRegister(reg2);
}


void XorOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "^";
    GetRight()->Print(stream);
    stream << '\n';
}



void BitwOrOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();


    GetLeft()->EmitRISC(stream, reg, context); // destination
    GetRight()->EmitRISC(stream, reg2, context); // other param

    stream << "\tor " << reg << ", " << reg << ", " << reg2 << std::endl;
    context.DeallocateRegister(reg2);
}


void BitwOrOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "|";
    GetRight()->Print(stream);
    stream << '\n';
}

}
