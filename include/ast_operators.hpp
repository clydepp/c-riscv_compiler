#pragma once
#include "ast_node.hpp"

namespace ast {

class Operator : public Node {
protected:
    NodePtr left;
    NodePtr right;
public:
    Operator(NodePtr left_, NodePtr right_) : left(std::move(left_)), right(std::move(right_)) {}
    virtual void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;
    const NodePtr& GetLeft() const { return left; }
    const NodePtr& GetRight() const { return right; }
};

class AddOp : public Operator {
public:
    AddOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class SubOp : public Operator {
public:
    SubOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class MulOp : public Operator {
public:
    MulOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class DivOp : public Operator {
public:
    DivOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class ModOp : public Operator {
    public:
        ModOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

        void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
        void Print(std::ostream& stream) const override;
    };


class BitwAndOp : public Operator {
public:
    BitwAndOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class XorOp : public Operator {
public:
    XorOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class BitwOrOp : public Operator {
public:
    BitwOrOp(NodePtr left_, NodePtr right_) : Operator(std::move(left_), std::move(right_)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};


} // namespace ast
