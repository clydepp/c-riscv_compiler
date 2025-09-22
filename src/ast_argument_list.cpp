#include "ast_argument_list.hpp"

namespace ast {

void ArgumentList::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    for (const auto& node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        reg = context.GetFreeRegister();
        node->EmitRISC(stream, reg, context);
    }
}

void ArgumentList::Print(std::ostream& stream) const {
    NodeList::Print(stream);
}

}
