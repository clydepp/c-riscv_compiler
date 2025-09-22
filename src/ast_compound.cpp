#include "ast_compound.hpp"

namespace ast {
void CompoundStatement::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    if (declaration_list_){
        std::cout << "compound statement declaration list" << std::endl;
        declaration_list_->EmitRISC(stream, reg, context);
    }
    if (statement_list_){
        std::cout << "entering compound statement list" << std::endl;
        statement_list_->EmitRISC(stream, reg, context);
    }
}
void CompoundStatement::Print(std::ostream& stream) const {
    if (declaration_list_)
        declaration_list_->Print(stream);
    if (statement_list_)
        statement_list_->Print(stream);
}
}
