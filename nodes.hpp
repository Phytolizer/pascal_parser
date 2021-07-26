#ifndef PASCAL_NODES_HPP
#define PASCAL_NODES_HPP

#include <optional>
#include <string>
#include <vector>

namespace Pascal
{

struct HintDirective
{
    enum class Type
    {
        Deprecated,
        Experimental,
        Platform,
        Unimplemented,
    };
    Type type;
    std::string message;
};

struct UnsignedInteger
{
    enum class Type
    {
        Decimal,
        Hexadecimal,
        Octal,
        Binary,
    };
    Type type;
    std::string value;
};

struct ScaleFactor
{
    std::string sign;
    std::string exponent;
};

struct UnsignedReal
{
    std::string value;
    std::optional<std::string> decimal_part;
    std::optional<ScaleFactor> scale_factor;
};

struct UnsignedNumber
{
    enum class Type
    {
        UnsignedReal,
        UnsignedInteger,
    };
    Type type;
    union {
        UnsignedReal *unsigned_real;
        UnsignedInteger *unsigned_integer;
    } value;
};

struct SignedNumber
{
    std::optional<std::string> sign;
    UnsignedNumber number;
};

struct Label
{
    enum class Type
    {
        DigitSequence,
        Identifier,
    };
    Type type;
    union {
        std::string *digit_sequence;
        std::string *identifier;
    } value;
};

struct CharacterStringElement
{
    enum class Type
    {
        QuotedString,
        ControlString,
    };
    Type type;
    std::string value;
};

struct CharacterString
{
    std::vector<CharacterStringElement> elements;
};

struct HintDirectives
{
    std::vector<HintDirective> values;
};

struct Expression // TODO
{
};

struct ConstantDeclaration
{
    std::string name;
    Expression expression;
    HintDirectives hint_directives;
};

struct ConstantDeclarations
{
    std::vector<ConstantDeclaration> values;
};

struct ParseNode
{
    enum class Type
    {
        HintDirective,
        HintDirectives,
        StringConstant,
        UnsignedInteger,
        UnsignedReal,
        UnsignedNumber,
        SignedNumber,
        ScaleFactor,
        Label,
        CharacterString,
        ConstantDeclaration,
        ConstantDeclarations,
    };
    Type type;

    union {
        HintDirective *hint_directive;
        UnsignedInteger *unsigned_integer;
        UnsignedReal *unsigned_real;
        UnsignedNumber *unsigned_number;
        SignedNumber *signed_number;
        ScaleFactor *scale_factor;
        std::string *string_constant;
        Label *label;
        CharacterString *character_string;
        Expression *expression;
        HintDirectives *hint_directives;
        ConstantDeclarations *constant_declarations;
        ConstantDeclaration *constant_declaration;
    } value;
};

} // namespace Pascal

#define D_ParseNode_User Pascal::ParseNode

#endif // PASCAL_NODES_HPP
