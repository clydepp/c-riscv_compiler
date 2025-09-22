#pragma once

#include "ast_node.hpp"

namespace ast{
class Case : public Node{
private:
    NodePtr constant_expression_;
    NodePtr statement_;
public:
    Case(NodePtr constant_expression, NodePtr statement) : constant_expression_(std::move(constant_expression)), statement_(std::move(statement)){}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};
}
