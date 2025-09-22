#pragma once

#include "ast_node.hpp"

namespace ast {
class InitDeclarator : public Node
{
private:
    NodePtr declarator_;
    NodePtr initializer_;

public:
    InitDeclarator(NodePtr declarator, NodePtr initializer) : declarator_(std::move(declarator)), initializer_(std::move(initializer)) {}

    virtual void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;

};

}
