#pragma once

#include "ast_node.hpp"
namespace ast {

// this is called for function declarations
class DirectDeclarator : public Node
{
private:
    NodePtr identifier_; // only this for function w/ no parameters
    NodeList* parameters_; // this is for a list of parameters

public:
    DirectDeclarator(NodePtr identifier, NodeList* parameters) : identifier_(std::move(identifier)), parameters_(std::move(parameters)){};

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
