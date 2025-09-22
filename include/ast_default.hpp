#pragma once

#include "ast_node.hpp"

namespace ast{
class Default : public Node {
private:
    NodePtr statement_;

public:
    Default(NodePtr statement) : statement_(std::move(statement)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
