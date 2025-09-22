#pragma once
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {
class ParamDeclaration : public Node {
private:
    const TypeSpecifier declaration_specifiers_; // Function TYPE
    NodePtr declarator_; // Function NAME
public:
    ParamDeclaration (TypeSpecifier declaration_specifiers, NodePtr declarator) : declaration_specifiers_(declaration_specifiers), declarator_(std::move(declarator)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
