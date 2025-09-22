#include "ast_node.hpp"

namespace ast {
class SizeOfVariable : public Node {
private:
    NodePtr expression_;
public:
    SizeOfVariable(NodePtr expression) : expression_(std::move(expression)) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

class SizeOfType : public Node {
private:
    NodePtr type_;
}
