#include "ast_case.hpp"

namespace ast{
    void Case::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const{
        std::string cond_reg = context.GetSwitchCondition();
        std::string case_label = context.GetUniqueLabel("case");
        std::string next_label = context.GetUniqueLabel("next_case");

        std::string value_reg = context.GetFreeRegister();
        constant_expression_->EmitRISC(stream, value_reg, context);

        stream << "\tbeq " << cond_reg << ", " << value_reg << ", " << case_label << std::endl;

        // Jump to next case if not equal
        stream << "\tj " << next_label << std::endl;

        stream << case_label << ":" << std::endl;
        statement_->EmitRISC(stream, reg, context);

        stream << next_label << ":" << std::endl;


        context.DeallocateRegister(value_reg);
    }

    void Case::Print(std::ostream& stream) const{
        stream << "\tcase ";
        constant_expression_->Print(stream);
        stream << ": ";
        statement_->Print(stream);
        stream << std::endl;
    }
}
