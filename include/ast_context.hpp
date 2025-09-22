#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "ast_identifier_case.hpp"
namespace ast {
// An object of class Context is passed between ast nodes during compilation.
// This can be used to pass around information about what's currently being
// compiled (e.g. function scope and variable names).

/* Features:
- manage all variables - global and local, depending on the scope
- anti-crashout function
- some register allocation/management
- pushing and popping registers to the stack
- allocating the stackframe for a certain function (let's keep this a fixed size)
- managing the stack pointer
- managing available registers

TWO DIFFERENT APPROACHES:
- don't use the stack at all, just use registers ** let's try and firm this one
- use the stack for everything (basically the -O0 code)

Notes:
- lemme load all int, double etc. values into a5 (look at how Godbolt does it)

*/
struct StackObject {
    int stack_offset;
    std::string variable_name = "";
    // needs a type here


    StackObject(){}
    StackObject(int stack_offset, std::string variable) : stack_offset(stack_offset), variable_name(variable) {}

};

class Context
{
private:
    std::unordered_map<int, bool> arg_register_usage { // false = unused, true = used
        {0, false}, {1, false}, {2, false}, {3, false},
        {4, false}, {5, false}, {6, false}, {7, false}
    };

    std::unordered_map<std::string, StackObject> variables_in_stack; // key: variable name, value: StackObject
    IdentifierCase ident_operation = IdentifierCase::DECL;

    std::unordered_map<std::string, int> label_map; // key is label type, value is the counter
    int reg_counter = 0;

    std::string switch_condition_reg_;
    std::string switch_end_label_;
    int label_counter_ = 0;

    std::stack<std::string> break_labels_;

protected:
    std::vector<StackObject> stack_sim {StackObject()}; // stack simulation with the 'top'
    int stack_offset = 1; // can be changed depending on the number of stackframes

    bool end_label = false;
    bool function_call = false;

    std::string current_funct_name = ""; // should be set for every declaration/definition (just for the sake of end labels)

    bool array_declaration = false;
    int array_size = 0;

    int temp_index = 0;
    bool array_index = false;

public:
    std::string current_array_name = "";
    std::string GetFreeRegister(); // checks a0-a7 for free registers
    int GetBaseOffset(std::string& value_name);

    void PrintStackSim();
    // changes the vector stack_sim
    void InitializeStackVect();
    void EndStackVect();

    void InitializeStack(std::ostream& stream); // stackframe for functions - will be called first
    void EndStack(std::ostream& stream); // stackframe for functions - will be called last

    std::string GetVariableReg(const std::string& variable);
    int GetVariableOffset(const std::string& variable); // returns the offset of a variable within its stackframe
    void SetIdentifierType(std::string& ident_case);
    void PrintIdentifierType();
    IdentifierCase GetIdentifierType();

    // tracking pointers
    void FindSP(); // register sp points to 'bottom' of stack
    void FindFP(); // frame pointer s0, points to 'top' of stack
    void FindRA(); // return address ra, points to the return address of the function

    // for control flow & labels
    std::string MakeLabel(const std::string& function);
    std::string MakeReg(const std::string& condition);

    void ValueOntoStack(std::string& ident_name, std::string& reg_name);
    void ArrayIndexOntoStack(std::string& array_name, int index);
    // void WriteToAllocation();

    void DeallocateRegister(std::string& reg);

    void ResetArgumentRegisters();

    void SetGlobalEndLabel(); // to be used in if, while and recursive RETURN
    bool CheckGlobalEnd();

    void SetFunctionName(std::string& ident);
    std::string GetFunctionName();

    void IsFunctionCall(bool funct_call);
    bool IfFunctionCall();

    void ResetUsedRegister(std::string& reg_name);
    void PrintArgRegisters();

    void SetArrayDeclaration(bool array_decl);
    bool GetArrayDeclaration();
    void SetArraySize(int size);
    int GetArraySize();

    bool GetArrayIndex();
    void SetArrayIndex(bool array_index);
    void SetTempIndex(int index);
    int GetTempIndex();

    std::string GetUniqueLabel(const std::string& prefix) {
        return prefix + "_" + std::to_string(label_counter_++);
    }

    void SetSwitchCondition(const std::string& reg) {
        switch_condition_reg_ = reg;
    }

    std::string GetSwitchCondition() const {
        return switch_condition_reg_;
    }

    void SetSwitchEndLabel(const std::string& label) {
        switch_end_label_ = label;
    }

    std::string GetSwitchEndLabel() const {
        return switch_end_label_;
    }

    void PushBreakLabel(const std::string& label) {
        break_labels_.push(label);
    }

    void PopBreakLabel() {
        if (!break_labels_.empty()) {
            break_labels_.pop();
        }
    }

    std::string GetCurrentBreakLabel() const {
        if (break_labels_.empty()) {
            throw std::runtime_error("No break label available");
        }
        return break_labels_.top();
    }

};

} // namespace ast
