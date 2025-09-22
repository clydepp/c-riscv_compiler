#pragma once

#include "ast_node.hpp"

namespace ast {

class FunctionCall : public Node {
private:
    NodePtr function_name_;
    NodeList* argument_expression_list_;

public:
    FunctionCall(NodePtr function_name, NodeList* argument_list) : function_name_(std::move(function_name)), argument_expression_list_(std::move(argument_list)){};

    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
