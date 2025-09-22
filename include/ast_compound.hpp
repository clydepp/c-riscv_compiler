#include "ast_node.hpp"

namespace ast {

// should implement {declaration_list statement_list}
class CompoundStatement : public Node
{
private:
    NodeList* declaration_list_;
    NodeList* statement_list_;

public:
    CompoundStatement(NodeList* declaration_list, NodeList* statement_list) : declaration_list_(declaration_list), statement_list_(statement_list) {}
    void EmitRISC(std::ostream& stream, std::string& reg, Context& context) const override;
    void Print(std::ostream& stream) const override;
};

}
