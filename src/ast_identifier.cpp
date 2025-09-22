#include "ast_identifier.hpp"

namespace ast {

void Identifier::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {

    IdentifierCase id = context.GetIdentifierType();
    std::string ident_copy = ident; // name of identifier/variable
    switch (id) {
        case IdentifierCase::ARRAY:
            context.current_array_name = ident;
            break;
        case IdentifierCase::FUNCT:
            stream << ident;
            if (!context.IfFunctionCall()){
                context.SetFunctionName(ident_copy);
            }
            break;
        case IdentifierCase::DECL:
            //stream << ".word " << ident << std::endl;
            break;
        case IdentifierCase::LOCAL_INIT:
            context.ValueOntoStack(ident_copy, reg);
            stream << "\tsw " << reg << ", -" << context.GetVariableOffset(ident) << "(s0)" << std::endl;
            break;
        case IdentifierCase::LOCAL_OPER:
            reg = context.GetFreeRegister();
            stream << "\tlw " << reg << ", -" << context.GetVariableOffset(ident) << "(s0)" << std::endl;
            break;
        case IdentifierCase::LOCAL_OVERWRITE:
            stream << "\tsw " << reg << ", -" << context.GetVariableOffset(ident) << "(s0)" << std::endl;
            break;
        default:
            throw std::runtime_error("Invalid identifier case");
    }
    std::cout << "printing stack simulation in identifer:" << std::endl;
    context.PrintStackSim();
}

void Identifier::Print(std::ostream& stream) const
{
    stream << ident;

}

}
