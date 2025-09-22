#pragma once

#include <string_view>
#include <stdexcept>
namespace ast {

enum class TypeSpecifier
{
    VOID,
    UNSIGNED_CHAR,
    CHAR,
    UNSIGNED_SHORT,
    SHORT,
    UNSIGNED_INT,
    INT,
    UNSIGNED_LONG,
    LONG,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE,
    STRUCT
};

template<typename LogStream>
LogStream& operator<<(LogStream& ls, const TypeSpecifier& type)
{
    const auto TypeToString = [&type] {
        switch (type)
        {
        case TypeSpecifier::VOID:
            return "void";
            break;
        case TypeSpecifier::UNSIGNED_CHAR:
            return "unsigned char";
            break;
        case TypeSpecifier::CHAR:
            return "char";
            break;
        case TypeSpecifier::UNSIGNED_SHORT:
            return "unsigned short";
            break;
        case TypeSpecifier::SHORT:
            return "short";
            break;
        case TypeSpecifier::UNSIGNED_INT:
            return "unsigned int";
            break;
        case TypeSpecifier::INT:
            return "int";
            break;
        case TypeSpecifier::UNSIGNED_LONG:
            return "unsigned long";
            break;
        case TypeSpecifier::LONG:
            return "long";
            break;
        case TypeSpecifier::FLOAT:
            return "float";
            break;
        case TypeSpecifier::DOUBLE:
            return "double";
            break;
        case TypeSpecifier::LONG_DOUBLE:
            return "long double";
            break;
        case TypeSpecifier::STRUCT:
            return "struct";
            break;
        }
        throw std::runtime_error("Unexpected type specifier");
    };
    return ls << TypeToString();
}

}
