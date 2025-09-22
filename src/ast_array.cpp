#include "ast_array.hpp"
#include "ast_context.hpp"

namespace ast {

// Emit RISC-V assembly for the array initialization
void Array::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    context.SetArrayDeclaration(true);
    size_->EmitRISC(stream, reg, context);
    context.SetArrayDeclaration(false);

    // write to stack_sim
    // first, find a free stack offset
    // then, use this as a base offset and add +i*4 for each element
    context.PrintStackSim();

    std::string ident_case = "array";
    context.SetIdentifierType(ident_case);
    name_->EmitRISC(stream, reg, context);
    std::string name = context.current_array_name;
    std::cout << "name of array: " << name << std::endl;

    int array_size = context.GetArraySize();
    for (int i = 0; i < array_size; ++i){
        std::cout << "add " << std::to_string(i*4) << " to stack offset" << std::endl;
        context.ArrayIndexOntoStack(name, i);
    }
    std::string arraybase = name + "[0]";
    int baseoffset = context.GetBaseOffset(arraybase); // find the base in the stack
    int temp_offset = 0;
    for (int a = 0; a < array_size; ++a){
        temp_offset = baseoffset + a*4;
        stream << "\tsw zero, " << -temp_offset << "(s0)" << std::endl;
    }
    context.PrintStackSim();
}

// Print the array definition
void Array::Print(std::ostream& stream) const {
    /*stream << (is_global_ ? "global " : "local ") << "array " << name_ << " = {";
    for (size_t i = 0; i < elements_.size(); ++i) {
        if (i > 0) stream << ", ";
        elements_[i]->Print(stream);  // Print the element
    }
    stream << "};" << std::endl;*/
    stream << "array!" << std::endl;

    // write to stack_sim
}

// Handle array access (reading or writing elements)
void ArrayAccess::EmitRISC(std::ostream& stream, std::string& reg, Context& context) const {
    std::string ident_case = "array";
    context.SetIdentifierType(ident_case);
    name_->EmitRISC(stream, reg, context);
    std::string name = context.current_array_name;
    std::cout << "name of array (for access): " << name << std::endl;
    std::string arraybase = name + "[0]";

    context.SetArrayIndex(true);
    index_->EmitRISC(stream, reg, context);
    context.SetArrayIndex(false);

    int index = context.GetTempIndex();
    int baseoffset = context.GetBaseOffset(arraybase);
    stream << "\tsw " << reg << ", " << -(baseoffset+(index*4)) << "(s0)" << std::endl;

}

// Print array access
void ArrayAccess::Print(std::ostream& stream) const {
    // stream << array_name_ << "[";
    // index_->Print(stream);
    // stream << "]";
    // if (is_write_) {
    //     stream << " = ";
    //     value_->Print(stream);
    // stream << ";" << std::endl;
    // }
    stream << "array access!" << std::endl;

}

} // namespace ast
