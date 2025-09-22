#pragma once

#include "ast_operators.hpp"
#include "ast_node.hpp"

namespace ast {

class ShiftLeft : public Operator {
public:
    ShiftLeft(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class ShiftRight : public Operator {
public:
    ShiftRight(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
