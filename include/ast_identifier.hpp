#pragma once

#include "ast_node.hpp"
#include "ast_identifier_case.hpp"

namespace ast {

class Identifier : public Node
{
private:
    std::string ident;
    // IdentifierCase identifier_case_;
public:
    Identifier(std::string identifier) : ident(std::move(identifier)){};

    virtual void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    virtual void Print(std::ostream& stream) const override;

    std::string GetIdentifierName() const { return ident; }

};

} // namespace ast
