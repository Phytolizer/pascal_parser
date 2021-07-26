#ifndef PASCAL_PARSER_PASCAL_NODES_HPP
#define PASCAL_PARSER_PASCAL_NODES_HPP

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace Pascal
{

struct VariableName;
struct FunctionName;
struct ProcedureName;
struct AccessName;
struct ConstantName;
struct String;
struct TypeName;
struct Name;
struct WithStatement;
struct CaseElement;
struct CaseStatement;
struct IfStatement;
struct ConditionalStatement;
struct FinalExpression;
struct InitialExpression;
struct ForStatement;
struct RepeatStatement;
struct WhileStatement;
struct RepetitiveStatement;
struct CompoundStatement;
struct StructuredStatement;
struct GotoStatement;
struct ProcedureStatement;
struct AssignmentStatement;
struct SimpleStatement;
struct Statement;
struct ElementList;
struct Set;
struct FunctionDesignator;
struct Factor;
struct MultiplicationOperator;
struct Term;
struct AdditionOperator;
struct SimpleExpression;
struct RelationalOperator;
struct Expression;
struct ActualVariable;
struct ActualFunction;
struct ActualProcedure;
struct ActualValue;
struct ActualParameter;
struct ActualParameterList;
struct FunctionParameters;
struct RecordAccess;
struct ArrayAccess;
struct EndAccess;
struct VariableAccess;
struct ExpressionList;
struct StatementSequence;
struct StatementPart;
struct FunctionHeading;
struct FunctionDeclaration;
struct ProcedureHeading;
struct ProcedureDeclaration;
struct Directive;
struct ProcedureAndFunctionDeclarationPart;
struct VariableDeclaration;
struct VariableDeclarationPart;
struct TypeDefinition;
struct TypeDefinitionPart;
struct ConstantDefinition;
struct ConstantDefinitionPart;
struct LabelDeclarationPart;
struct DeclarationPart;
struct FunctionType;
struct ProcedureType;
struct ProceduralType;
struct PointerType;
struct FileComponentType;
struct FileType;
struct BaseType;
struct SetType;
struct Variant;
struct TagField;
struct VariantPart;
struct RecordSection;
struct FixedPart;
struct FieldList;
struct RecordType;
struct ElementType;
struct IndexType;
struct ArrayType;
struct UnpackedStructuredType;
struct StructuredType;
struct EnumeratedType;
struct SubrangeType;
struct SimpleType;
struct Type;
struct CaseLabelList;
struct Constant;
struct ParameterType;
struct FormalParameterSection;
struct FormalParameterList;
struct Number;
struct Label;
struct Block;
struct ProgramHeading;
struct IdentifierList;
struct Program;

enum class Sign
{
    Positive,
    Negative,
};

struct Name
{
    std::string value;
};

struct VariableName
{
    Name name;
};

struct FunctionName
{
    Name name;
};

struct ProcedureName
{
    Name name;
};

struct AccessName
{
    Name name;
};

struct ConstantName
{
    Name name;
};

struct String
{
    std::string value;
};

struct TypeName
{
    
};

struct WithStatement
{
};

struct CaseElement
{
};

struct CaseStatement
{
};

struct IfStatement
{
};

struct ConditionalStatement
{
};

struct FinalExpression
{
};

struct InitialExpression
{
};

struct ForStatement
{
};

struct RepeatStatement
{
};

struct WhileStatement
{
};

struct RepetitiveStatement
{
};

struct CompoundStatement
{
};

struct StructuredStatement
{
};

struct GotoStatement
{
};

struct ProcedureStatement
{
};

struct AssignmentStatement
{
};

struct SimpleStatement
{
};

struct Statement
{
};

struct ElementList
{
};

struct Set
{
};

struct FunctionDesignator
{
};

struct Factor
{
};

struct MultiplicationOperator
{
};

struct Term
{
};

struct AdditionOperator
{
};

struct SimpleExpression
{
};

struct RelationalOperator
{
};

struct Expression
{
};

struct ActualVariable
{
};

struct ActualFunction
{
};

struct ActualProcedure
{
};

struct ActualValue
{
};

struct ActualParameter
{
};

struct ActualParameterList
{
};

struct FunctionParameters
{
};

struct RecordAccess
{
};

struct ArrayAccess
{
};

struct EndAccess
{
};

struct VariableAccess
{
};

struct ExpressionList
{
};

struct StatementSequence
{
};

struct StatementPart
{
};

struct FunctionHeading
{
};

struct FunctionDeclaration
{
};

struct ProcedureHeading
{
};

struct ProcedureDeclaration
{
};

struct Directive
{
};

struct ProcedureAndFunctionDeclarationPart
{
};

struct VariableDeclaration
{
};

struct VariableDeclarationPart
{
};

struct TypeDefinition
{
};

struct TypeDefinitionPart
{
};

struct ConstantDefinition
{
};

struct ConstantDefinitionPart
{
};

struct LabelDeclarationPart
{
};

struct DeclarationPart
{
};

struct FunctionType
{
};

struct ProcedureType
{
};

struct ProceduralType
{
};

struct PointerType
{
};

struct FileComponentType
{
};

struct FileType
{
};

struct BaseType
{
};

struct SetType
{
};

struct Variant
{
};

struct TagField
{
};

struct VariantPart
{
};

struct RecordSection
{
};

struct FixedPart
{
};

struct FieldList
{
};

struct RecordType
{
};

struct ElementType
{
};

struct IndexType
{
};

struct ArrayType
{
};

struct UnpackedStructuredType
{
};

struct StructuredType
{
};

struct EnumeratedType
{
};

struct SubrangeType
{
};

struct SimpleType
{
};

struct Type
{
};

struct CaseLabelList
{
};

struct Constant
{
};

struct ParameterType
{
};

struct FormalParameterSection
{
};

struct FormalParameterList
{
};

struct Number
{
};

struct Label
{
};

struct Block
{
};

struct ProgramHeading
{
};

struct IdentifierList
{
};

struct Program
{
};

struct Node
{
    enum class Type
    {
        Program,
        IdentifierList,
        ProgramHeading,
        Block,
        Label,
        Number,
        FormalParameterList,
        FormalParameterSection,
        ParameterType,
        Constant,
        CaseLabelList,
        Type,
        SimpleType,
        SubrangeType,
        EnumeratedType,
        StructuredType,
        UnpackedStructuredType,
        ArrayType,
        IndexType,
        ElementType,
        RecordType,
        FieldList,
        FixedPart,
        RecordSection,
        VariantPart,
        TagField,
        Variant,
        SetType,
        BaseType,
        FileType,
        FileComponentType,
        PointerType,
        ProceduralType,
        ProcedureType,
        FunctionType,
        DeclarationPart,
        LabelDeclarationPart,
        ConstantDefinitionPart,
        ConstantDefinition,
        TypeDefinitionPart,
        TypeDefinition,
        VariableDeclarationPart,
        VariableDeclaration,
        ProcedureAndFunctionDeclarationPart,
        Directive,
        ProcedureDeclaration,
        ProcedureHeading,
        FunctionDeclaration,
        FunctionHeading,
        StatementPart,
        StatementSequence,
        ExpressionList,
        VariableAccess,
        EndAccess,
        ArrayAccess,
        RecordAccess,
        FunctionParameters,
        ActualParameterList,
        ActualParameter,
        ActualValue,
        ActualProcedure,
        ActualFunction,
        ActualVariable,
        Expression,
        RelationalOperator,
        SimpleExpression,
        AdditionOperator,
        Term,
        MultiplicationOperator,
        Factor,
        FunctionDesignator,
        Set,
        ElementList,
        Statement,
        SimpleStatement,
        AssignmentStatement,
        ProcedureStatement,
        GotoStatement,
        StructuredStatement,
        CompoundStatement,
        RepetitiveStatement,
        WhileStatement,
        RepeatStatement,
        ForStatement,
        InitialExpression,
        FinalExpression,
        ConditionalStatement,
        IfStatement,
        CaseStatement,
        CaseElement,
        WithStatement,
        Name,
        TypeName,
        String,
        ConstantName,
        AccessName,
        ProcedureName,
        FunctionName,
        VariableName,
    } type;

    union {
        Program *program;
        IdentifierList *identifier_list;
        ProgramHeading *program_heading;
        Block *block;
        Label *label;
        Number *number;
        FormalParameterList *formal_parameter_list;
        FormalParameterSection *formal_parameter_section;
        ParameterType *parameter_type;
        Constant *constant;
        CaseLabelList *case_label_list;
        Type *type;
        SimpleType *simple_type;
        SubrangeType *subrange_type;
        EnumeratedType *enumerated_type;
        StructuredType *structured_type;
        UnpackedStructuredType *unpacked_structured_type;
        ArrayType *array_type;
        IndexType *index_type;
        ElementType *element_type;
        RecordType *record_type;
        FieldList *field_list;
        FixedPart *fixed_part;
        RecordSection *record_section;
        VariantPart *variant_part;
        TagField *tag_field;
        Variant *variant;
        SetType *set_type;
        BaseType *base_type;
        FileType *file_type;
        FileComponentType *file_component_type;
        PointerType *pointer_type;
        ProceduralType *procedural_type;
        ProcedureType *procedure_type;
        FunctionType *function_type;
        DeclarationPart *declaration_part;
        LabelDeclarationPart *label_declaration_part;
        ConstantDefinitionPart *constant_definition_part;
        ConstantDefinition *constant_definition;
        TypeDefinitionPart *type_definition_part;
        TypeDefinition *type_definition;
        VariableDeclarationPart *variable_declaration_part;
        VariableDeclaration *variable_declaration;
        ProcedureAndFunctionDeclarationPart *procedure_and_function_declaration_part;
        Directive *directive;
        ProcedureDeclaration *procedure_declaration;
        ProcedureHeading *procedure_heading;
        FunctionDeclaration *function_declaration;
        FunctionHeading *function_heading;
        StatementPart *statement_part;
        StatementSequence *statement_sequence;
        ExpressionList *expression_list;
        VariableAccess *variable_access;
        EndAccess *end_access;
        ArrayAccess *array_access;
        RecordAccess *record_access;
        FunctionParameters *function_parameters;
        ActualParameterList *actual_parameter_list;
        ActualParameter *actual_parameter;
        ActualValue *actual_value;
        ActualProcedure *actual_procedure;
        ActualFunction *actual_function;
        ActualVariable *actual_variable;
        Expression *expression;
        RelationalOperator *relational_operator;
        SimpleExpression *simple_expression;
        AdditionOperator *addition_operator;
        Term *term;
        MultiplicationOperator *multiplication_operator;
        Factor *factor;
        FunctionDesignator *function_designator;
        Set *set;
        ElementList *element_list;
        Statement *statement;
        SimpleStatement *simple_statement;
        AssignmentStatement *assignment_statement;
        ProcedureStatement *procedure_statement;
        GotoStatement *goto_statement;
        StructuredStatement *structured_statement;
        CompoundStatement *compound_statement;
        RepetitiveStatement *repetitive_statement;
        WhileStatement *while_statement;
        RepeatStatement *repeat_statement;
        ForStatement *for_statement;
        InitialExpression *initial_expression;
        FinalExpression *final_expression;
        ConditionalStatement *conditional_statement;
        IfStatement *if_statement;
        CaseStatement *case_statement;
        CaseElement *case_element;
        WithStatement *with_statement;
        Name *name;
        TypeName *type_name;
        String *string;
        ConstantName *constant_name;
        AccessName *access_name;
        ProcedureName *procedure_name;
        FunctionName *function_name;
        VariableName *variable_name;
    } u;

    ~Node()
    {
        _destroy();
    }
    Node(const Node &other) = delete;
    Node &operator=(const Node &other) = delete;
    Node(Node &&other) : type{other.type}
    {
        _move(std::move(other));
    }
    Node &operator=(Node &&other)
    {
        if (&other != this)
        {
            _destroy();
            _move(std::move(other));
        }
        return *this;
    }

  private:
    void _destroy()
    {
        switch (type)
        {
        case Type::Program:
            delete u.program;
            break;
        case Type::IdentifierList:
            delete u.identifier_list;
            break;
        case Type::ProgramHeading:
            delete u.program_heading;
            break;
        case Type::Block:
            delete u.block;
            break;
        case Type::Label:
            delete u.label;
            break;
        case Type::Number:
            delete u.number;
            break;
        case Type::FormalParameterList:
            delete u.formal_parameter_list;
            break;
        case Type::FormalParameterSection:
            delete u.formal_parameter_section;
            break;
        case Type::ParameterType:
            delete u.parameter_type;
            break;
        case Type::Constant:
            delete u.constant;
            break;
        case Type::CaseLabelList:
            delete u.case_label_list;
            break;
        case Type::Type:
            delete u.type;
            break;
        case Type::SimpleType:
            delete u.simple_type;
            break;
        case Type::SubrangeType:
            delete u.subrange_type;
            break;
        case Type::EnumeratedType:
            delete u.enumerated_type;
            break;
        case Type::StructuredType:
            delete u.structured_type;
            break;
        case Type::UnpackedStructuredType:
            delete u.unpacked_structured_type;
            break;
        case Type::ArrayType:
            delete u.array_type;
            break;
        case Type::IndexType:
            delete u.index_type;
            break;
        case Type::ElementType:
            delete u.element_type;
            break;
        case Type::RecordType:
            delete u.record_type;
            break;
        case Type::FieldList:
            delete u.field_list;
            break;
        case Type::FixedPart:
            delete u.fixed_part;
            break;
        case Type::RecordSection:
            delete u.record_section;
            break;
        case Type::VariantPart:
            delete u.variant_part;
            break;
        case Type::TagField:
            delete u.tag_field;
            break;
        case Type::Variant:
            delete u.variant;
            break;
        case Type::SetType:
            delete u.set_type;
            break;
        case Type::BaseType:
            delete u.base_type;
            break;
        case Type::FileType:
            delete u.file_type;
            break;
        case Type::FileComponentType:
            delete u.file_component_type;
            break;
        case Type::PointerType:
            delete u.pointer_type;
            break;
        case Type::ProceduralType:
            delete u.procedural_type;
            break;
        case Type::ProcedureType:
            delete u.procedure_type;
            break;
        case Type::FunctionType:
            delete u.function_type;
            break;
        case Type::DeclarationPart:
            delete u.declaration_part;
            break;
        case Type::LabelDeclarationPart:
            delete u.label_declaration_part;
            break;
        case Type::ConstantDefinitionPart:
            delete u.constant_definition_part;
            break;
        case Type::ConstantDefinition:
            delete u.constant_definition;
            break;
        case Type::TypeDefinitionPart:
            delete u.type_definition_part;
            break;
        case Type::TypeDefinition:
            delete u.type_definition;
            break;
        case Type::VariableDeclarationPart:
            delete u.variable_declaration_part;
            break;
        case Type::VariableDeclaration:
            delete u.variable_declaration;
            break;
        case Type::ProcedureAndFunctionDeclarationPart:
            delete u.procedure_and_function_declaration_part;
            break;
        case Type::Directive:
            delete u.directive;
            break;
        case Type::ProcedureDeclaration:
            delete u.procedure_declaration;
            break;
        case Type::ProcedureHeading:
            delete u.procedure_heading;
            break;
        case Type::FunctionDeclaration:
            delete u.function_declaration;
            break;
        case Type::FunctionHeading:
            delete u.function_heading;
            break;
        case Type::StatementPart:
            delete u.statement_part;
            break;
        case Type::StatementSequence:
            delete u.statement_sequence;
            break;
        case Type::ExpressionList:
            delete u.expression_list;
            break;
        case Type::VariableAccess:
            delete u.variable_access;
            break;
        case Type::EndAccess:
            delete u.end_access;
            break;
        case Type::ArrayAccess:
            delete u.array_access;
            break;
        case Type::RecordAccess:
            delete u.record_access;
            break;
        case Type::FunctionParameters:
            delete u.function_parameters;
            break;
        case Type::ActualParameterList:
            delete u.actual_parameter_list;
            break;
        case Type::ActualParameter:
            delete u.actual_parameter;
            break;
        case Type::ActualValue:
            delete u.actual_value;
            break;
        case Type::ActualProcedure:
            delete u.actual_procedure;
            break;
        case Type::ActualFunction:
            delete u.actual_function;
            break;
        case Type::ActualVariable:
            delete u.actual_variable;
            break;
        case Type::Expression:
            delete u.expression;
            break;
        case Type::RelationalOperator:
            delete u.relational_operator;
            break;
        case Type::SimpleExpression:
            delete u.simple_expression;
            break;
        case Type::AdditionOperator:
            delete u.addition_operator;
            break;
        case Type::Term:
            delete u.term;
            break;
        case Type::MultiplicationOperator:
            delete u.multiplication_operator;
            break;
        case Type::Factor:
            delete u.factor;
            break;
        case Type::FunctionDesignator:
            delete u.function_designator;
            break;
        case Type::Set:
            delete u.set;
            break;
        case Type::ElementList:
            delete u.element_list;
            break;
        case Type::Statement:
            delete u.statement;
            break;
        case Type::SimpleStatement:
            delete u.simple_statement;
            break;
        case Type::AssignmentStatement:
            delete u.assignment_statement;
            break;
        case Type::ProcedureStatement:
            delete u.procedure_statement;
            break;
        case Type::GotoStatement:
            delete u.goto_statement;
            break;
        case Type::StructuredStatement:
            delete u.structured_statement;
            break;
        case Type::CompoundStatement:
            delete u.compound_statement;
            break;
        case Type::RepetitiveStatement:
            delete u.repetitive_statement;
            break;
        case Type::WhileStatement:
            delete u.while_statement;
            break;
        case Type::RepeatStatement:
            delete u.repeat_statement;
            break;
        case Type::ForStatement:
            delete u.for_statement;
            break;
        case Type::InitialExpression:
            delete u.initial_expression;
            break;
        case Type::FinalExpression:
            delete u.final_expression;
            break;
        case Type::ConditionalStatement:
            delete u.conditional_statement;
            break;
        case Type::IfStatement:
            delete u.if_statement;
            break;
        case Type::CaseStatement:
            delete u.case_statement;
            break;
        case Type::CaseElement:
            delete u.case_element;
            break;
        case Type::WithStatement:
            delete u.with_statement;
            break;
        case Type::Name:
            delete u.name;
            break;
        case Type::TypeName:
            delete u.type_name;
            break;
        case Type::String:
            delete u.string;
            break;
        case Type::ConstantName:
            delete u.constant_name;
            break;
        case Type::AccessName:
            delete u.access_name;
            break;
        case Type::ProcedureName:
            delete u.procedure_name;
            break;
        case Type::FunctionName:
            delete u.function_name;
            break;
        case Type::VariableName:
            delete u.variable_name;
            break;
        }
    }

    void _move(Node &&other)
    {
        switch (type)
        {
        case Type::Program:
            u.program = other.u.program;
            other.u.program = nullptr;
            break;
        case Type::IdentifierList:
            u.identifier_list = other.u.identifier_list;
            other.u.identifier_list = nullptr;
            break;
        case Type::ProgramHeading:
            u.program_heading = other.u.program_heading;
            other.u.program_heading = nullptr;
            break;
        case Type::Block:
            u.block = other.u.block;
            other.u.block = nullptr;
            break;
        case Type::Label:
            u.label = other.u.label;
            other.u.label = nullptr;
            break;
        case Type::Number:
            u.number = other.u.number;
            other.u.number = nullptr;
            break;
        case Type::FormalParameterList:
            u.formal_parameter_list = other.u.formal_parameter_list;
            other.u.formal_parameter_list = nullptr;
            break;
        case Type::FormalParameterSection:
            u.formal_parameter_section = other.u.formal_parameter_section;
            other.u.formal_parameter_section = nullptr;
            break;
        case Type::ParameterType:
            u.parameter_type = other.u.parameter_type;
            other.u.parameter_type = nullptr;
            break;
        case Type::Constant:
            u.constant = other.u.constant;
            other.u.constant = nullptr;
            break;
        case Type::CaseLabelList:
            u.case_label_list = other.u.case_label_list;
            other.u.case_label_list = nullptr;
            break;
        case Type::Type:
            u.type = other.u.type;
            other.u.type = nullptr;
            break;
        case Type::SimpleType:
            u.simple_type = other.u.simple_type;
            other.u.simple_type = nullptr;
            break;
        case Type::SubrangeType:
            u.subrange_type = other.u.subrange_type;
            other.u.subrange_type = nullptr;
            break;
        case Type::EnumeratedType:
            u.enumerated_type = other.u.enumerated_type;
            other.u.enumerated_type = nullptr;
            break;
        case Type::StructuredType:
            u.structured_type = other.u.structured_type;
            other.u.structured_type = nullptr;
            break;
        case Type::UnpackedStructuredType:
            u.unpacked_structured_type = other.u.unpacked_structured_type;
            other.u.unpacked_structured_type = nullptr;
            break;
        case Type::ArrayType:
            u.array_type = other.u.array_type;
            other.u.array_type = nullptr;
            break;
        case Type::IndexType:
            u.index_type = other.u.index_type;
            other.u.index_type = nullptr;
            break;
        case Type::ElementType:
            u.element_type = other.u.element_type;
            other.u.element_type = nullptr;
            break;
        case Type::RecordType:
            u.record_type = other.u.record_type;
            other.u.record_type = nullptr;
            break;
        case Type::FieldList:
            u.field_list = other.u.field_list;
            other.u.field_list = nullptr;
            break;
        case Type::FixedPart:
            u.fixed_part = other.u.fixed_part;
            other.u.fixed_part = nullptr;
            break;
        case Type::RecordSection:
            u.record_section = other.u.record_section;
            other.u.record_section = nullptr;
            break;
        case Type::VariantPart:
            u.variant_part = other.u.variant_part;
            other.u.variant_part = nullptr;
            break;
        case Type::TagField:
            u.tag_field = other.u.tag_field;
            other.u.tag_field = nullptr;
            break;
        case Type::Variant:
            u.variant = other.u.variant;
            other.u.variant = nullptr;
            break;
        case Type::SetType:
            u.set_type = other.u.set_type;
            other.u.set_type = nullptr;
            break;
        case Type::BaseType:
            u.base_type = other.u.base_type;
            other.u.base_type = nullptr;
            break;
        case Type::FileType:
            u.file_type = other.u.file_type;
            other.u.file_type = nullptr;
            break;
        case Type::FileComponentType:
            u.file_component_type = other.u.file_component_type;
            other.u.file_component_type = nullptr;
            break;
        case Type::PointerType:
            u.pointer_type = other.u.pointer_type;
            other.u.pointer_type = nullptr;
            break;
        case Type::ProceduralType:
            u.procedural_type = other.u.procedural_type;
            other.u.procedural_type = nullptr;
            break;
        case Type::ProcedureType:
            u.procedure_type = other.u.procedure_type;
            other.u.procedure_type = nullptr;
            break;
        case Type::FunctionType:
            u.function_type = other.u.function_type;
            other.u.function_type = nullptr;
            break;
        case Type::DeclarationPart:
            u.declaration_part = other.u.declaration_part;
            other.u.declaration_part = nullptr;
            break;
        case Type::LabelDeclarationPart:
            u.label_declaration_part = other.u.label_declaration_part;
            other.u.label_declaration_part = nullptr;
            break;
        case Type::ConstantDefinitionPart:
            u.constant_definition_part = other.u.constant_definition_part;
            other.u.constant_definition_part = nullptr;
            break;
        case Type::ConstantDefinition:
            u.constant_definition = other.u.constant_definition;
            other.u.constant_definition = nullptr;
            break;
        case Type::TypeDefinitionPart:
            u.type_definition_part = other.u.type_definition_part;
            other.u.type_definition_part = nullptr;
            break;
        case Type::TypeDefinition:
            u.type_definition = other.u.type_definition;
            other.u.type_definition = nullptr;
            break;
        case Type::VariableDeclarationPart:
            u.variable_declaration_part = other.u.variable_declaration_part;
            other.u.variable_declaration_part = nullptr;
            break;
        case Type::VariableDeclaration:
            u.variable_declaration = other.u.variable_declaration;
            other.u.variable_declaration = nullptr;
            break;
        case Type::ProcedureAndFunctionDeclarationPart:
            u.procedure_and_function_declaration_part =
                new ProcedureAndFunctionDeclarationPart{*other.u.procedure_and_function_declaration_part};
            break;
        case Type::Directive:
            u.directive = other.u.directive;
            other.u.directive = nullptr;
            break;
        case Type::ProcedureDeclaration:
            u.procedure_declaration = other.u.procedure_declaration;
            other.u.procedure_declaration = nullptr;
            break;
        case Type::ProcedureHeading:
            u.procedure_heading = other.u.procedure_heading;
            other.u.procedure_heading = nullptr;
            break;
        case Type::FunctionDeclaration:
            u.function_declaration = other.u.function_declaration;
            other.u.function_declaration = nullptr;
            break;
        case Type::FunctionHeading:
            u.function_heading = other.u.function_heading;
            other.u.function_heading = nullptr;
            break;
        case Type::StatementPart:
            u.statement_part = other.u.statement_part;
            other.u.statement_part = nullptr;
            break;
        case Type::StatementSequence:
            u.statement_sequence = other.u.statement_sequence;
            other.u.statement_sequence = nullptr;
            break;
        case Type::ExpressionList:
            u.expression_list = other.u.expression_list;
            other.u.expression_list = nullptr;
            break;
        case Type::VariableAccess:
            u.variable_access = other.u.variable_access;
            other.u.variable_access = nullptr;
            break;
        case Type::EndAccess:
            u.end_access = other.u.end_access;
            other.u.end_access = nullptr;
            break;
        case Type::ArrayAccess:
            u.array_access = other.u.array_access;
            other.u.array_access = nullptr;
            break;
        case Type::RecordAccess:
            u.record_access = other.u.record_access;
            other.u.record_access = nullptr;
            break;
        case Type::FunctionParameters:
            u.function_parameters = other.u.function_parameters;
            other.u.function_parameters = nullptr;
            break;
        case Type::ActualParameterList:
            u.actual_parameter_list = other.u.actual_parameter_list;
            other.u.actual_parameter_list = nullptr;
            break;
        case Type::ActualParameter:
            u.actual_parameter = other.u.actual_parameter;
            other.u.actual_parameter = nullptr;
            break;
        case Type::ActualValue:
            u.actual_value = other.u.actual_value;
            other.u.actual_value = nullptr;
            break;
        case Type::ActualProcedure:
            u.actual_procedure = other.u.actual_procedure;
            other.u.actual_procedure = nullptr;
            break;
        case Type::ActualFunction:
            u.actual_function = other.u.actual_function;
            other.u.actual_function = nullptr;
            break;
        case Type::ActualVariable:
            u.actual_variable = other.u.actual_variable;
            other.u.actual_variable = nullptr;
            break;
        case Type::Expression:
            u.expression = other.u.expression;
            other.u.expression = nullptr;
            break;
        case Type::RelationalOperator:
            u.relational_operator = other.u.relational_operator;
            other.u.relational_operator = nullptr;
            break;
        case Type::SimpleExpression:
            u.simple_expression = other.u.simple_expression;
            other.u.simple_expression = nullptr;
            break;
        case Type::AdditionOperator:
            u.addition_operator = other.u.addition_operator;
            other.u.addition_operator = nullptr;
            break;
        case Type::Term:
            u.term = other.u.term;
            other.u.term = nullptr;
            break;
        case Type::MultiplicationOperator:
            u.multiplication_operator = other.u.multiplication_operator;
            other.u.multiplication_operator = nullptr;
            break;
        case Type::Factor:
            u.factor = other.u.factor;
            other.u.factor = nullptr;
            break;
        case Type::FunctionDesignator:
            u.function_designator = other.u.function_designator;
            other.u.function_designator = nullptr;
            break;
        case Type::Set:
            u.set = other.u.set;
            other.u.set = nullptr;
            break;
        case Type::ElementList:
            u.element_list = other.u.element_list;
            other.u.element_list = nullptr;
            break;
        case Type::Statement:
            u.statement = other.u.statement;
            other.u.statement = nullptr;
            break;
        case Type::SimpleStatement:
            u.simple_statement = other.u.simple_statement;
            other.u.simple_statement = nullptr;
            break;
        case Type::AssignmentStatement:
            u.assignment_statement = other.u.assignment_statement;
            other.u.assignment_statement = nullptr;
            break;
        case Type::ProcedureStatement:
            u.procedure_statement = other.u.procedure_statement;
            other.u.procedure_statement = nullptr;
            break;
        case Type::GotoStatement:
            u.goto_statement = other.u.goto_statement;
            other.u.goto_statement = nullptr;
            break;
        case Type::StructuredStatement:
            u.structured_statement = other.u.structured_statement;
            other.u.structured_statement = nullptr;
            break;
        case Type::CompoundStatement:
            u.compound_statement = other.u.compound_statement;
            other.u.compound_statement = nullptr;
            break;
        case Type::RepetitiveStatement:
            u.repetitive_statement = other.u.repetitive_statement;
            other.u.repetitive_statement = nullptr;
            break;
        case Type::WhileStatement:
            u.while_statement = other.u.while_statement;
            other.u.while_statement = nullptr;
            break;
        case Type::RepeatStatement:
            u.repeat_statement = other.u.repeat_statement;
            other.u.repeat_statement = nullptr;
            break;
        case Type::ForStatement:
            u.for_statement = other.u.for_statement;
            other.u.for_statement = nullptr;
            break;
        case Type::InitialExpression:
            u.initial_expression = other.u.initial_expression;
            other.u.initial_expression = nullptr;
            break;
        case Type::FinalExpression:
            u.final_expression = other.u.final_expression;
            other.u.final_expression = nullptr;
            break;
        case Type::ConditionalStatement:
            u.conditional_statement = other.u.conditional_statement;
            other.u.conditional_statement = nullptr;
            break;
        case Type::IfStatement:
            u.if_statement = other.u.if_statement;
            other.u.if_statement = nullptr;
            break;
        case Type::CaseStatement:
            u.case_statement = other.u.case_statement;
            other.u.case_statement = nullptr;
            break;
        case Type::CaseElement:
            u.case_element = other.u.case_element;
            other.u.case_element = nullptr;
            break;
        case Type::WithStatement:
            u.with_statement = other.u.with_statement;
            other.u.with_statement = nullptr;
            break;
        case Type::Name:
            u.name = other.u.name;
            other.u.name = nullptr;
            break;
        case Type::TypeName:
            u.type_name = other.u.type_name;
            other.u.type_name = nullptr;
            break;
        case Type::String:
            u.string = other.u.string;
            other.u.string = nullptr;
            break;
        case Type::ConstantName:
            u.constant_name = other.u.constant_name;
            other.u.constant_name = nullptr;
            break;
        case Type::AccessName:
            u.access_name = other.u.access_name;
            other.u.access_name = nullptr;
            break;
        case Type::ProcedureName:
            u.procedure_name = other.u.procedure_name;
            other.u.procedure_name = nullptr;
            break;
        case Type::FunctionName:
            u.function_name = other.u.function_name;
            other.u.function_name = nullptr;
            break;
        case Type::VariableName:
            u.variable_name = other.u.variable_name;
            other.u.variable_name = nullptr;
            break;
        }
    }
};

} // namespace Pascal

#endif // PASCAL_PARSER_PASCAL_NODES_HPP
