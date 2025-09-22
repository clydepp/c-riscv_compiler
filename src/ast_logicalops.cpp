#include "ast_logicalops.hpp"

namespace ast {
void AndOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();
    std::string zero_label = context.MakeLabel("zero_case");
    std::string one_label = context.MakeLabel("one_case");

    GetLeft()->EmitRISC(stream, reg, context); 
    stream << "\tbeq " << reg << ", zero, ." << zero_label << std::endl;

    GetRight()->EmitRISC(stream, reg2, context);
    stream << "\tbeq " << reg2 << ", zero, ." << zero_label<< std::endl;
    stream << "\tli " << reg << ", 1" << std::endl;
    stream << "\tj ." << one_label << std::endl;
    stream << "." <<zero_label << ": " << std::endl;

    stream << "\tli " << reg << ",0" << std::endl;
    stream << "." << one_label << ": " << std::endl;

    context.DeallocateRegister(reg2);
}


void AndOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "&&";
    GetRight()->Print(stream);
    stream << '\n';
}

void OrOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context)const
{
    std::string ident_case = "local_oper";
    context.SetIdentifierType(ident_case);
    std::string reg2 = context.GetFreeRegister();
    std::string zero_label = context.MakeLabel(".zero_case");
    std::string one_label = context.MakeLabel(".one_case");
    std::string one_two = context.MakeLabel (".one_two");

    GetLeft()->EmitRISC(stream, reg, context); // destination
    // other param
    stream << "\tbne " << reg << ", zero, " << one_label << std::endl;

    GetRight()->EmitRISC(stream, reg2, context);
    stream << "\tbeq " << reg2 << ", zero, " << zero_label<< std::endl;


    stream << one_label << ": " << std::endl;
    stream << "\tli " << reg << ",1" << std::endl;
    stream << "\tj " << one_two << std::endl;



    stream <<  zero_label << ": " << std::endl;
    stream << "\tli "<< reg << ",0" << std::endl;

    stream << one_two << ": " << std::endl;


    context.DeallocateRegister(reg);
}


void OrOp::Print(std::ostream& stream) const
{
    stream << '\t';
    GetLeft()->Print(stream);
    stream << "||";
    GetRight()->Print(stream);
    stream << '\n';
}


}
