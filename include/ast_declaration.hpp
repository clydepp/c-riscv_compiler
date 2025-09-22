#pragma once

#include "ast_node.hpp"
#include "ast_type_specifier.hpp"

namespace ast {
class Declaration : public Node
{
private:
    const TypeSpecifier decl_specifier_; // pointer to a type specifier?
    NodePtr init_decl_list_; // points to init_declarator

public:
    Declaration(TypeSpecifier decl_specifier, NodePtr init_decl_list) : decl_specifier_(decl_specifier), init_decl_list_(std::move(init_decl_list)) {}

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override; // in init_declarator, EmitRISC will have three parameters
    void Print(std::ostream& stream) const override;

};

}
