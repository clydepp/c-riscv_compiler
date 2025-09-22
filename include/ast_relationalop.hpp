#include "ast_operators.hpp"

namespace ast {
class LessThan : public Operator {
public:
    LessThan(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class LessThanEq : public Operator {
public:
    LessThanEq(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class GreaterThan : public Operator {
public:
    GreaterThan(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class GreaterThanEq : public Operator {
public:
    GreaterThanEq(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};
}
