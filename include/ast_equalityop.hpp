#pragma once

#include "ast_operators.hpp"

namespace ast {
class EqualOp : public Operator {
public:
    EqualOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class NotEqualOp : public Operator {
public:
    NotEqualOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
