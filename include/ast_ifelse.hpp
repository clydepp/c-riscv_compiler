#pragma once

#include "ast_node.hpp"

namespace ast {
class IfElse : public Node
{
private:
    NodePtr condition_;
    NodePtr if_body_;
    NodePtr else_body_;
public:
    IfElse(NodePtr condition, NodePtr if_body, NodePtr else_body = nullptr) : condition_(std::move(condition)), if_body_(std::move(if_body)), else_body_(std::move(else_body)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
