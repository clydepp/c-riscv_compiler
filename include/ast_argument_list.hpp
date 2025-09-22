#pragma once
#include "ast_node.hpp"

namespace ast {
class ArgumentList : public NodeList {
public:
    using NodeList::NodeList;

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};
}
