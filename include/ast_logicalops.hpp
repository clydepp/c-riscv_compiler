#include "ast_operators.hpp"

namespace ast {
class AndOp : public Operator {
public:
    AndOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class OrOp : public Operator {
public:
    OrOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};
}
