#pragma once


#include "ast_node.hpp"


namespace ast {


class While : public Node
{
private:
    NodePtr condition_;// will have to decide between Node Ptr and std::unique_ptr
    NodePtr body_;

public:
    While(NodePtr condition, NodePtr body) : condition_(std::move(condition)), body_(std::move(body)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};


} // namespace ast
