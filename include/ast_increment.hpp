#pragma once

#include "ast_node.hpp"
#include "ast_incr_operator.hpp"

namespace ast {

class RightIncrement : public Node
{
private:
    NodePtr postfix_expression_;
    IncrementOper incr_operator_;

public:
    RightIncrement(NodePtr postfix_expression, IncrementOper increment_oper) : postfix_expression_(std::move(postfix_expression)), incr_operator_(increment_oper) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class LeftIncrement : public Node
{
private:
    NodePtr unary_expression_;
    IncrementOper incr_operator_;

public:
    LeftIncrement(NodePtr unary_expression, IncrementOper increment_oper) : unary_expression_(std::move(unary_expression)),incr_operator_(increment_oper) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}

