#pragma once

#include "ast_node.hpp"

namespace ast {
class Assignment : public Node
{
private:
    NodePtr unary_ex_;
    // assignment_operator assignment_operator;
    NodePtr assign_ex_ = nullptr;
public:
    Assignment(NodePtr unary_ex, NodePtr assign_ex) : unary_ex_(std::move(unary_ex)), assign_ex_(std::move(assign_ex)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override; // in init_declarator, EmitRISC will have three parameters
    void Print(std::ostream& stream) const override;
};

}
