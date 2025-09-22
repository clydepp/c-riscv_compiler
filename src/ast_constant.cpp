#include "ast_constant.hpp"

namespace ast {

void IntConstant::EmitRISC(std::ostream& stream, std::string& reg, Context& context)  const
{
    if (context.GetArrayDeclaration()){
        context.SetArraySize(value_);
    }
    else if (context.GetArrayIndex()){
        context.SetTempIndex(value_);
    }
    else
        stream << "\tli " << reg << ", "<< value_ << std::endl;
}

void IntConstant::Print(std::ostream& stream) const
{
    stream << value_;
}

} // namespace ast
