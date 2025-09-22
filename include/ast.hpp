#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_identifier_case.hpp" // scoped enum for different identifier cases
#include "ast_identifier.hpp"
#include "ast_jump_statement.hpp"
#include "ast_context.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_constant.hpp"
#include "ast_incr_operator.hpp"
#include "ast_increment.hpp"
#include "ast_argument_list.hpp"

// ===== simple implementations ===== //
#include "ast_operators.hpp"
#include "ast_declaration.hpp"
#include "ast_init_declarator.hpp"
#include "ast_assignment.hpp"
#include "ast_array.hpp"
#include "ast_for.hpp"
#include "ast_param_declarator.hpp"
#include "ast_relationalop.hpp"
#include "ast_equalityop.hpp"
#include "ast_logicalops.hpp"

// ===== control flow ===== //
#include "ast_ifelse.hpp"
#include "ast_while.hpp"
#include "ast_compound.hpp"
#include "ast_shifts.hpp"
#include "ast_function_call.hpp"
#include "ast_ternary.hpp"
#include "ast_switch.hpp"
#include "ast_case.hpp"
#include "ast_default.hpp"
#include "ast_break.hpp"

ast::NodePtr ParseAST(std::string file_name);
