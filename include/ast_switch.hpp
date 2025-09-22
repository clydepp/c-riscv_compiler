#pragma once

#include "ast_node.hpp"

namespace ast{

class SwitchStatement : public Node{

private:
    NodePtr expression_;
    NodePtr statement_;

public:
SwitchStatement(NodePtr expression, NodePtr statement) : expression_(std::move(expression)), statement_(std::move(statement)){}
void EmitRISC (std::ostream& stream, std::string& reg, Context& context) const override; // in init_declarator, EmitRISC will have three parameters
void Print(std::ostream& stream) const override;
};

}
