#pragma once

#include "ast_node.hpp"
#include "ast_context.hpp"
namespace ast {

class Array : public Node {
private:
    NodePtr name_;
    NodePtr size_; // constant_expression
    // bool is_global_; // Flag to check if it's a global array or not

public:
    Array(NodePtr name, NodePtr size) : name_(std::move(name)), size_(std::move(size)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class ArrayAccess : public Node {
private:
    NodePtr name_;
    NodePtr index_;

public:
    ArrayAccess(NodePtr name, NodePtr index) : name_(std::move(name)), index_(std::move(index)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

} // namespace ast
