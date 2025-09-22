#pragma once

#include "ast_node.hpp"

namespace ast {
class TernaryOp : public Node
{
private:
    NodePtr condition_;
    NodePtr true_exp_;
    NodePtr false_exp_;

public:
    TernaryOp(NodePtr condition, NodePtr true_exp, NodePtr false_exp) : condition_(std::move(condition)), true_exp_(std::move(true_exp)), false_exp_(std::move(false_exp)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
