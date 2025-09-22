#include "ast_context.hpp"

const int fixed_stacksize = 96; // just for now
namespace ast {

void Context::PrintStackSim(){
    for (auto& stack_obj : stack_sim){
        std::cout << "Stack Offset: " << stack_obj.stack_offset << " Contents in offset: " << stack_obj.variable_name << std::endl;
    }
}

void Context::ArrayIndexOntoStack(std::string& array_name, int index){
    int counter = 2;
    for (auto& stack_obj : stack_sim){
        if (stack_obj.variable_name == ""){
            stack_obj.stack_offset = counter*4;
            stack_obj.variable_name = array_name + "[" + std::to_string(index) + "]";

            return;
        }
        counter++;
    }
    throw std::runtime_error("No more space on stack");
}

int Context::GetBaseOffset(std::string& value_name){
    for (auto& stack_obj : stack_sim){
        if (stack_obj.variable_name == value_name){
            return stack_obj.stack_offset;
        }
    }
    throw std::runtime_error("Value not found in stack");
}

void Context::ValueOntoStack(std::string& ident_name, std::string&) {
    int counter = 2;
    for (auto& stack_obj : stack_sim){
        if (stack_obj.variable_name == ""){
            stack_obj.stack_offset = counter*4;
            stack_obj.variable_name = ident_name;

            variables_in_stack.insert({ident_name, stack_obj});
            return;
        }
        counter++;
    }
    throw std::runtime_error("No more space on stack");
}

std::string Context::GetFreeRegister() {
    for (int i =0; i < 8; ++i){
        if (arg_register_usage[i] == false){
            arg_register_usage[i] = true;
            return "a" + std::to_string(i);
        }
    }
    throw std::runtime_error("No free registers available");
}

void Context::InitializeStackVect(){
    int new_stack_idx = fixed_stacksize/4; // number of vector elements to add (12)
    for (int i = 0; i < new_stack_idx; i++){
        stack_sim.push_back(StackObject());
    }

    // Note: it's lazy but what can i do
    stack_offset += new_stack_idx;
    stack_sim[new_stack_idx-1].stack_offset = stack_offset*4; // holds the stack offset value
    stack_sim[new_stack_idx-1].variable_name = "sp"; // what register holds it/what register it stores for

    stack_sim[stack_offset-new_stack_idx].stack_offset = (stack_offset-new_stack_idx)*4;
    stack_sim[stack_offset-new_stack_idx].variable_name = "ra"; // also held in ra

    stack_sim[stack_offset-new_stack_idx+1].stack_offset = (stack_offset-new_stack_idx+1)*4;
    stack_sim[stack_offset-new_stack_idx+1].variable_name = "";

    stack_sim[stack_offset-new_stack_idx-1].stack_offset = (stack_offset-new_stack_idx-1)*4;
    stack_sim[stack_offset-new_stack_idx-1].variable_name = "s0"; // held in s0
}

void Context::EndStackVect(){
    // implement stack_sim later
}

void Context::InitializeStack(std::ostream& stream) {
    stream << "\taddi sp, sp, -" << fixed_stacksize << std::endl;
    stream << "\tsw ra, " << (fixed_stacksize-4) << "(sp)" << std::endl;
    stream << "\tsw s0, " << (fixed_stacksize-8) << "(sp)" << std::endl; // Godbolt stores the return address for base functions
    stream << "\taddi s0, sp, " << fixed_stacksize << std::endl;

    InitializeStackVect();
}

void Context::EndStack(std::ostream& stream) {
    stream << "\tlw ra, " << (fixed_stacksize-4) << "(sp)" << std::endl;
    stream << "\tlw s0, " << (fixed_stacksize-8) << "(sp)" << std::endl;
    stream << "\taddi sp, sp, " << fixed_stacksize << std::endl;
    stream << "\tjr ra" << std::endl;

    EndStackVect();
}

int Context::GetVariableOffset(const std::string& variable) {
    if (variables_in_stack.find(variable) == variables_in_stack.end())
        throw std::runtime_error("Variable not found in stack");
    else
        return variables_in_stack[variable].stack_offset;
}

void Context::SetIdentifierType(std::string& ident_case) {
    if (ident_case == "funct") ident_operation = IdentifierCase::FUNCT;
    else if (ident_case == "array") ident_operation = IdentifierCase::ARRAY;
    else if (ident_case == "global_decl") ident_operation = IdentifierCase::DECL;
    else if (ident_case == "local_init") ident_operation = IdentifierCase::LOCAL_INIT;
    else if (ident_case == "local_oper") ident_operation = IdentifierCase::LOCAL_OPER;
    else if (ident_case == "local_overwrite") ident_operation = IdentifierCase::LOCAL_OVERWRITE;
    else throw std::runtime_error("Invalid identifier case");
}

IdentifierCase Context::GetIdentifierType() {
    return ident_operation;
}

std::string Context::MakeLabel(const std::string& function) {
    int& label_counter = label_map[function];
    label_counter++;
    return function + std::to_string(label_counter);
}

std::string Context::MakeReg(const std::string& condition) {
    reg_counter++;
    return "reg_" + condition + "_" + std::to_string(reg_counter);
}

void Context::DeallocateRegister(std::string& reg) {
    int reg_num = std::stoi(reg.substr(1));
    arg_register_usage[reg_num] = false;
}

/*std::string Context::GetVariableReg(const std::string& variable){
    auto var = variables_in_stack.find(variable);
    if (var != variables_in_stack.end())
        return var->second.variable_name;
    else throw std::runtime_error("Variable can't be returned from stack");
} */

void Context::ResetArgumentRegisters(){
    for (int i =0; i < 8; ++i){
        arg_register_usage[i] = false;
    }
    if (arg_register_usage[0] == false) std::cout << "a0 is false (checker)" << std::endl;
}

void Context::SetGlobalEndLabel(){
    if (end_label == false)
        end_label = true;
}

bool Context::CheckGlobalEnd(){
    if (end_label == true)
        return true; // prints label
    return false;
}

void Context::SetFunctionName(std::string& ident){
    current_funct_name = ident;
}

std::string Context::GetFunctionName(){
    return current_funct_name;
}

void Context::IsFunctionCall(bool funct_call){
    function_call = funct_call;
}

bool Context::IfFunctionCall(){
    return function_call;
}

void Context::ResetUsedRegister(std::string& reg_name){ // for function call
    int reg_num = std::stoi(reg_name.substr(1));
    arg_register_usage[reg_num] = true;
}

void Context::PrintArgRegisters(){
    for (int i =0; i < 8; ++i){
        std::cout << arg_register_usage[i] << " ";
    }
    std::cout << std::endl;
}

void Context::SetArrayDeclaration(bool array_decl){ // is this an array declaration??
    array_declaration = array_decl;
}

bool Context::GetArrayDeclaration(){
    return array_declaration;
}

void Context::SetArraySize(int size){
    array_size = size;
}

int Context::GetArraySize(){
    return array_size;
}

void Context::SetArrayIndex(bool array_index_bool){
    array_index = array_index_bool;
}

bool Context::GetArrayIndex(){
    return array_index;
}

void Context::SetTempIndex(int index){
    temp_index = index;
}

int Context::GetTempIndex(){
    return temp_index;
}

} // namespace ast
