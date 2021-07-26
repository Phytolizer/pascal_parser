{
#include "nodes.hpp"

}
${declare save_parse_tree}

// ============================================================================
// =                             Pascal Tokens                                =
// ============================================================================
identifier: "[a-zA-Z_][a-zA-Z0-9_]*";


// Hint directives (used for diagnostics)

hint_directive: 'deprecated'/i 
    {
        $$.type = Pascal::ParseNode::Type::HintDirective;
        $$.value.hint_directive = new Pascal::HintDirective{ .type = Pascal::HintDirective::Type::Deprecated };
    }
        (
            string_constant
            {
                $$.value.hint_directive->message = *$1.value.string_constant;
                delete $1.value.string_constant;
            }
        )?
    | 'experimental'/i
    {
        $$.type = Pascal::ParseNode::Type::HintDirective;
        $$.value.hint_directive = new Pascal::HintDirective{ .type = Pascal::HintDirective::Type::Experimental };
    }
    | 'platform'/i
    {
        $$.type = Pascal::ParseNode::Type::HintDirective;
        $$.value.hint_directive = new Pascal::HintDirective{ .type = Pascal::HintDirective::Type::Platform };
    }
    | 'unimplemented'/i
    {
        $$.type = Pascal::ParseNode::Type::HintDirective;
        $$.value.hint_directive = new Pascal::HintDirective{ .type = Pascal::HintDirective::Type::Unimplemented };
    }
    ;


// The string constant that will be used in a diagnostic.

string_constant: "'([^']|'')*'"
    {
        $$.type = Pascal::ParseNode::Type::StringConstant;
        $$.value.string_constant = new std::string{$n.start_loc.s, $n.end};
    }
    ;


// Basic tokens.

hex_digit_sequence: "[0-9a-fA-F]+";
octal_digit_sequence: "[0-7]+";
binary_digit_sequence: "[01]+";
digit_sequence: "[0-9]+";


// Numbers.

unsigned_integer: digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::UnsignedInteger;
        $$.value.unsigned_integer = new Pascal::UnsignedInteger{ .type = Pascal::UnsignedInteger::Type::Decimal };
        $$.value.unsigned_integer->value = std::string{$n.start_loc.s, $n.end};
    }
    |
    '$' hex_digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::UnsignedInteger;
        $$.value.unsigned_integer = new Pascal::UnsignedInteger{ .type = Pascal::UnsignedInteger::Type::Hexadecimal };
        $$.value.unsigned_integer->value = std::string{$n1.start_loc.s, $n1.end};
    }
    |
    '&' octal_digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::UnsignedInteger;
        $$.value.unsigned_integer = new Pascal::UnsignedInteger{ .type = Pascal::UnsignedInteger::Type::Octal };
        $$.value.unsigned_integer->value = std::string{$n1.start_loc.s, $n1.end};
    }
    |
    '%' binary_digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::UnsignedInteger;
        $$.value.unsigned_integer = new Pascal::UnsignedInteger{ .type = Pascal::UnsignedInteger::Type::Binary };
        $$.value.unsigned_integer->value = std::string{$n1.start_loc.s, $n1.end};
    }
    ;

sign: "[+-]";

unsigned_real: digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::UnsignedReal;
        $$.value.unsigned_real = new Pascal::UnsignedReal{ .value = std::string{$n.start_loc.s, $n.end} };
    }
    (
        '.' digit_sequence
        {
            $$.value.unsigned_real->decimal_part = std::string{$n1.start_loc.s, $n1.end};
        }
    )?
    (
        scale_factor
        {
            $$.value.unsigned_real->scale_factor = *$1.value.scale_factor;
            delete $1.value.scale_factor;
        }
    )?
    ;

scale_factor: "[eE]"
    {
        $$.type = Pascal::ParseNode::Type::ScaleFactor;
        $$.value.scale_factor = new Pascal::ScaleFactor{};
    }
    (
        sign
        {
            $$.value.scale_factor->sign = std::string{$n.start_loc.s, $n.end};
        }
    )?
    digit_sequence
    {
        $$.value.scale_factor->exponent = std::string{$n.start_loc.s, $n.end};
    }
    ;

unsigned_number: unsigned_real
    {
        $$.type = Pascal::ParseNode::Type::UnsignedNumber;
        $$.value.unsigned_number = new Pascal::UnsignedNumber{ .type = Pascal::UnsignedNumber::Type::UnsignedReal };
        $$.value.unsigned_number->value.unsigned_real = $1.value.unsigned_real;
        delete $1.value.unsigned_real;
    }
    |
    unsigned_integer
    {
        $$.type = Pascal::ParseNode::Type::UnsignedNumber;
        $$.value.unsigned_number = new Pascal::UnsignedNumber{ .type = Pascal::UnsignedNumber::Type::UnsignedInteger };
        $$.value.unsigned_number->value.unsigned_integer = $1.value.unsigned_integer;
    }
    ;

signed_number: 
    (
        sign
        {
            $$.type = Pascal::ParseNode::Type::SignedNumber;
            $$.value.signed_number = new Pascal::SignedNumber{ .sign = std::string{$n.start_loc.s, $n.end} };
        }
    )?
    unsigned_number
    {
        $$.type = Pascal::ParseNode::Type::SignedNumber;
        if ($# == 1) {
            $$.value.signed_number = new Pascal::SignedNumber{ .sign = {} };
        }
        $$.value.signed_number->number = *$1.value.unsigned_number;
        delete $1.value.unsigned_number;
    }
    ;


// Labels.

label: digit_sequence
    {
        $$.type = Pascal::ParseNode::Type::Label;
        $$.value.label = new Pascal::Label{ .type = Pascal::Label::Type::DigitSequence };
        $$.value.label->value.digit_sequence = new std::string{$n.start_loc.s, $n.end};
    }
    |
    identifier
    {
        $$.type = Pascal::ParseNode::Type::Label;
        $$.value.label = new Pascal::Label{ .type = Pascal::Label::Type::Identifier };
        $$.value.label->value.identifier = new std::string{$n.start_loc.s, $n.end};
    }
    ;


// Strings.

character_string: 
    (
        quoted_string
        {
            $$.type = Pascal::ParseNode::Type::CharacterString;
            $$.value.character_string = new Pascal::CharacterString{};
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::QuotedString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
        |
        control_string
        {
            $$.type = Pascal::ParseNode::Type::CharacterString;
            $$.value.character_string = new Pascal::CharacterString{};
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::ControlString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
        |
        caret_string
        {
            $$.type = Pascal::ParseNode::Type::CharacterString;
            $$.value.character_string = new Pascal::CharacterString{};
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::CaretString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
    )
    (
        quoted_string
        {
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::QuotedString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
        |
        control_string
        {
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::ControlString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
        |
        caret_string
        {
            $$.value.character_string->elements.emplace_back(Pascal::CharacterStringElement{
                .type = Pascal::CharacterStringElement::Type::CaretString,
                .value = std::string{$n.start_loc.s, $n.end},
            });
        }
    )*
    ;


// Character string elements.

quoted_string: "'([^']|'')*'";
control_string: 
    (
        '#' unsigned_integer
        {
            delete $2.value.unsigned_integer;
        }
    )+
    ;
caret_string: "^[a-zA-Z]";


// Constant declarations.

constant_declaration: 
    constant_declaration
    {
        $$.type = Pascal::ParseNode::Type::ConstantDeclarations;
        $$.value.constant_declarations = new Pascal::ConstantDeclarations {
            .values = std::vector<Pascal::ConstantDeclaration>{*$1.value.constant_declaration},
        };
        delete $1.value.constant_declaration;
    }
    (
        constant_declaration
        {
            $$.value.constant_declarations->values.emplace_back(*$1.value.constant_declaration);
            delete $1.value.constant_declaration;
        }
    )*
    ;

constant_declaration: identifier '=' expression hint_directives ';'
    {
        $$.type = Pascal::ParseNode::Type::ConstantDeclaration;
        $$.value.constant_declaration = new Pascal::ConstantDeclaration {
            .name = std::string{$n1.start_loc.s, $n1.end},
            .expression = *$3.value.expression,
            .hint_directives = *$4.value.hint_directives,
        };
        delete $3.value.expression;
        delete $4.value.hint_directives;
    }
    ;

hint_directives:
    hint_directive
    {
        $$.type = Pascal::ParseNode::Type::HintDirectives;
        $$.value.hint_directives = new Pascal::HintDirectives {
            .values = std::vector<Pascal::HintDirective>{*$1.value.hint_directive},
        };
        delete $1.value.hint_directive;
    }
    (
        hint_directive
        {
            $$.value.hint_directives->values.emplace_back(*$1.value.hint_directive);
            delete $1.value.hint_directive;
        }
    )*
    ;

typed_constant_declarations:
    typed_constant_declaration
    {
        $$.type = Pascal::ParseNode::Type::TypedConstantDeclarations;
        $$.value.typed_constant_declarations = new Pascal::TypedConstantDeclarations{
            .values = std::vector<Pascal::TypedConstantDeclaration>{*$1.value.typed_constant_declaration},
        };
        delete $1.value.typed_constant_declaration;
    }
    (
        typed_constant_declaration
        {
            $$.value.typed_constant_declarations->values.emplace_back(*$1.value.typed_constant_declaration);
            delete $1.value.typed_constant_declaration;
        }
    )*
    ;

typed_constant_declaration: identifier ':' type '=' typed_constant hint_directive ';'
    {
        $$.type = Pascal::ParseNode::Type::TypedConstantDeclaration;
        $$.value.typed_constant_declaration = new Pascal::TypedConstantDeclaration{
            .name = std::string{$n1.start_loc.s, $n1.end},
            .type = *$3.value.type,
            .value = *$5.value.typed_constant,
            .hint_directive = *$6.value.hint_directive,
        };
        delete $3.value.type;
        delete $5.value.typed_constant;
        delete $6.value.hint_directive;
    }
    ;

typed_constant:
    expression
    {
        $$.type = Pascal::ParseNode::Type::TypedConstant;
        $$.value.typed_constant = new Pascal::TypedConstant{ .type = Pascal::TypedConstant::Type::Constant };
        $$.value.typed_constant->value.constant = $1.value.constant;
    }
    |
    address_constant
    {
        $$.type = Pascal::ParseNode::Type::TypedConstant;
        $$.value.typed_constant = new Pascal::TypedConstant{ .type = Pascal::TypedConstant::Type::AddressConstant };
        $$.value.typed_constant->value.address_constant = $1.value.address_constant;
    }
    |
    array_constant
    {
        $$.type = Pascal::ParseNode::Type::TypedConstant;
        $$.value.typed_constant = new Pascal::TypedConstant{ .type = Pascal::TypedConstant::Type::ArrayConstant };
        $$.value.typed_constant->value.array_constant = $1.value.array_constant;
    }
    |
    record_constant
    {
        $$.type = Pascal::ParseNode::Type::TypedConstant;
        $$.value.typed_constant = new Pascal::TypedConstant{ .type = Pascal::TypedConstant::Type::RecordConstant };
        $$.value.typed_constant->value.record_constant = $1.value.record_constant;
    }
    |
    procedural_constant
    {
        $$.type = Pascal::ParseNode::Type::TypedConstant;
        $$.value.typed_constant = new Pascal::TypedConstant{ .type = Pascal::TypedConstant::Type::ProceduralConstant };
        $$.value.typed_constant->value.procedural_constant = $1.value.procedural_constant;
    }
    ;

resourcestring_block:
    'resourcestring'/i 
    {
        $$.type = Pascal::ParseNode::Type::ResourceStringBlock;
        $$.value.resource_string_block = new Pascal::ResourceStringBlock{};
    }
    (
        resourcestring_element
        {
            $$.value.resource_string_block->values.emplace_back(std::move(*$1.value.resource_string_element));
            delete $1.value.resource_string_element;
        }
    )*
    ;

resourcestring_element:
    identifier '=' expression
    {
        $$.type = Pascal::ParseNode::Type::ResourceStringElement;
        $$.value.resource_string_element = new Pascal::ResourceStringElement{
            .name = std::string{$n1.start_loc.s, $n1.end},
            .value = std::move(*$3.value.expression),
        };
        delete $3.value.expression;
    }
    ;

type_declaration: identifier '=' type
    {
        $$.type = Pascal::ParseNode::Type::TypeDeclaration;
        $$.value.type_declaration = new Pascal::TypeDeclaration{
            .name = std::string{$n1.start_loc.s, $n1.end},
            .type = std::move(*$3.value.type),
        };
        delete $3.value.type;
    }
    (
        hint_directives
        {
            $$.value.type_declaration->hint_directives = std::move(*$1.value.hint_directives);
            delete $1.value.hint_directives;
        }
    )?
    ';'
    ;

type:
    simple_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::SimpleType };
        $$.value.type->value.simple_type = $1.value.simple_type;
    }
    |
    string_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::StringType };
        $$.value.type->value.string_type = $1.value.string_type;
    }
    |
    structured_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::StructuredType };
        $$.value.type->value.structured_type = $1.value.structured_type;
    }
    |
    pointer_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::PointerType };
        $$.value.type->value.pointer_type = $1.value.pointer_type;
    }
    |
    procedural_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::ProceduralType };
        $$.value.type->value.procedural_type = $1.value.procedural_type;
    }
    |
    generic_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::GenericType };
        $$.value.type->value.generic_type = $1.value.generic_type;
    }
    |
    specialized_type
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::SpecializedType };
        $$.value.type->value.specialized_type = $1.value.specialized_type;
    }
    |
    type_alias
    {
        $$.type = Pascal::ParseNode::Type::Type;
        $$.value.type = new Pascal::Type{ .type = Pascal::Type::Type::TypeAlias };
        $$.value.type->value.type_alias = $1.value.type_alias;
    }
    ;

simple_type: ordinal_type
    {
        $$.type = Pascal::ParseNode::Type::SimpleType;
        $$.value.simple_type = new Pascal::SimpleType { .type = Pascal::SimpleType::Type::OrdinalType };
        $$.value.simple_type->value.ordinal_type = $1.value.ordinal_type;
    }
    |
    real_type
    {
        $$.type = Pascal::ParseNode::Type::SimpleType;
        $$.value.simple_type = new Pascal::SimpleType { .type = Pascal::SimpleType::Type::RealType };
        $$.value.simple_type->value.real_type = $1.value.real_type;
    }
    ;

real_type: real_type_identifier
    {
        $$.type = Pascal::ParseNode::Type::RealType;
        $$.value.real_type = new Pascal::RealType { .identifier = std::string{$n1.start_loc.s, $n1.end} };
    }
    ;

ordinal_type: identifier
    {
        $$.type = Pascal::ParseNode::Type::OrdinalType;
        $$.value.ordinal_type = new Pascal::OrdinalType { .type = Pascal::OrdinalType::Type::Identifier };
        $$.value.ordinal_type->value.identifier = new std::string{$n.start_loc.s, $n.end};
    }
    |
    signed_number '..' signed_number
    {
        $$.type = Pascal::ParseNode::Type::OrdinalType;
        $$.value.ordinal_type = new Pascal::OrdinalType { .type = Pascal::OrdinalType::Type::RangeType };
        $$.value.ordinal_type->value.range_type = new Pascal::OrdinalType::RangeType{
            .begin = *$1.value.signed_number,
            .end = *$3.value.signed_number,
        };
        delete $1.value.signed_number;
        delete $3.value.signed_number;
    }
    |
    '('
    {
        $$.type = Pascal::ParseNode::Type::OrdinalType;
        $$.value.ordinal_type = new Pascal::OrdinalType { .type = Pascal::OrdinalType::Type::EnumeratedType };
        $$.value.ordinal_type->value.enumerated_type = new Pascal::OrdinalType::EnumeratedType{};
    }
    enumeration_constant
    {
        $$.value.ordinal_type->value.enumerated_type->values.emplace_back(std::move(*$1.value.enumeration_constant));
    }
    (
        ',' enumeration_constant
        {
            $$.value.ordinal_type->value.enumerated_type->values.emplace_back(std::move(*$1.value.enumeration_constant));
        }
    )*
    ','? ')'
    ;

enumeration_constant:
    identifier
    {
        $$.type = Pascal::ParseNode::Type::EnumerationConstant;
        $$.value.enumeration_constant = new Pascal::OrdinalType::EnumeratedType::EnumerationConstant{ 
            .name = std::string{$n.start_loc.s, $n.end},
        }
    }
    (
        ('=' | ':=') expression
        {
            $$.value.enumeration_constant->value = *$1.value.expression;
            delete $1.value.expression;
        }
    )?
    ;

string_type: 'string'
    {
        $$.type = Pascal::ParseNode::Type::StringType;
        $$.value.string_type = new Pascal::StringType{ .type = Pascal::StringType::Type::FixedString };
    }
    (
        '[' expression ']'
        {
            $$.value.string_type->width = *$2.value.expression;
            delete $2.value.expression;
        }
    )?
    |
    'type'/i ('string'/i | 'ansistring'/i) '(' expression ')'
    {
        $$.type = Pascal::ParseNode::Type::StringType;
        $$.value.string_type = new Pascal::StringType{ .type = Pascal::StringType::Type::AnsiString };
        $$.value.string_type->codepage = *$4.value.expression;
        delete $4.value.expression;
    }
    ;

structured_type: array_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::ArrayType };
        $$.value.structured_type->value.array_type = $1.value.array_type;
    }
    |
    record_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::RecordType };
        $$.value.structured_type->value.record_type = $1.value.record_type;
    }
    |
    object_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::ObjectType };
        $$.value.structured_type->value.object_type = $1.value.object_type;
    }
    |
    class_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::ClassType };
        $$.value.structured_type->value.class_type = $1.value.class_type;
    }
    |
    class_reference_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::ClassReferenceType };
        $$.value.structured_type->value.class_reference_type = $1.value.class_reference_type;
    }
    |
    interface_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::InterfaceType };
        $$.value.structured_type->value.interface_type = $1.value.interface_type;
    }
    |
    set_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::SetType };
        $$.value.structured_type->value.set_type = $1.value.set_type;
    }
    |
    file_type
    {
        $$.type = Pascal::ParseNode::Type::StructuredType;
        $$.value.structured_type = new Pascal::StructuredType{ .type = Pascal::StructuredType::Type::FileType };
        $$.value.structured_type->value.file_type = $1.value.file_type;
    }
    ;

array_type: 
    (
        'packed'/i
        {
            $$.type = Pascal::ParseNode::Type::ArrayType;
            $$.value.array_type = new Pascal::ArrayType{ .packed = true; }
        }
        |
        'bitpacked'/i
        {
            $$.type = Pascal::ParseNode::Type::ArrayType;
            $$.value.array_type = new Pascal::ArrayType{ .bitpacked = true; }
        }
    )?
    'array'/i
    {
        if ($# == 1)
        {
            $$.type = Pascal::ParseNode::Type::ArrayType;
            $$.value.array_type = new Pascal::ArrayType{};
        }
    }
    (
        '[' ordinal_type_list ']'
        {
            $$.value.array_type->index_range = *$2.value.ordinal_type_list;
            delete $2.value.ordinal_type_list;
        }
    )?
    'of'/i type
    {
        $$.value.array_type->element_type = *$2.value.type;
        delete $2.value.type;
    }
    ;

ordinal_type_list: ordinal_type
    {
        $$.type = Pascal::ParseNode::Type::OrdinalTypeList;
        $$.value.ordinal_type_list = new Pascal::OrdinalTypeList{};
        $$.value.ordinal_type_list->values.emplace_back(std::move(*$1.value.ordinal_type));
        delete $1.value.ordinal_type;
    }
    (
        ',' ordinal_type
        {
            $$.value.ordinal_type_list->values.emplace_back(std::move(*$2.value.ordinal_type));
            delete $2.value.ordinal_type;
        }
    )*
    ;

record_type:
    (
        'packed'/i
        {
            $$.type = Pascal::ParseNode::Type::RecordType;
            $$.value.record_type = new Pascal::RecordType{ .packed = true; }
        }
        |
        'bitpacked'/i
        {
            $$.type = Pascal::ParseNode::Type::RecordType;
            $$.value.record_type = new Pascal::RecordType{ .bitpacked = true; }
        }
    )?
    'record'/i
    {
        if ($# == 1)
        {
            $$.type = Pascal::ParseNode::Type::RecordType;
            $$.value.record_type = new Pascal::RecordType{};
        }
    }
    field_list 'end'/i
    {
        $$.value.record_type->fields = std::move(*$1.value.field_list);
        delete $1.value.field_list;
    }
    ;

field_list: 
    (
        (
            fixed_fields ';'
            {
                $$.type = Pascal::ParseNode::Type::FieldList;
                $$.value.field_list = new Pascal::FieldList{ .fixed_fields = std::move(*$1.value.fixed_fields) };
                delete $1.value.fixed_fields;
            }
        )?
        variant_part
        {
            if ($# == 1)
            {
                $$.type = Pascal::ParseNode::Type::FieldList;
                $$.value.field_list = new Pascal::FieldList{ .variant_part = std::move(*$1.value.variant_part) };
                delete $1.value.variant_part;
            }
        }
    )
    |
    fixed_fields ';'?
    {
        $$.type = Pascal::ParseNode::Type::FieldList;
        $$.value.field_list = new Pascal::FieldList{ .fixed_fields = std::move(*$1.value.fixed_fields) };
        delete $1.value.fixed_fields;
    }
    ;

expression: 'TODO';

whitespace: "[ \t\r\n\f\v]+";
