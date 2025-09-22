#include "ast_ternary.hpp"
#include <string>

namespace ast {
void TernaryOp::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const
{
    std::cout << "enters ternary operation" << std::endl;

    condition_->EmitRISC(stream, reg, context);
    std::cout << "prints condition" << std::endl;

    std::string true_label = context.MakeLabel("ternary_true");
    std::string false_label = context.MakeLabel("ternary_false");
    std::string end_label = context.MakeLabel("ternary_end");

    stream << "\tbnez " << reg << ", " << true_label << std::endl;

    stream << false_label << ":" << std::endl;
    false_exp_->EmitRISC(stream, reg, context);
    stream << "\tj " << end_label << std::endl;

    stream << true_label << ":" <<std::endl;
    true_exp_->EmitRISC(stream, reg, context);

    stream << end_label << ":" << std::endl;
}
void TernaryOp::Print(std::ostream& stream) const{
    stream << "(";
    condition_->Print(stream);
    stream << " ? ";
    true_exp_->Print(stream);
    stream << " : ";
    false_exp_->Print(stream);
    stream << ")";
}

}
