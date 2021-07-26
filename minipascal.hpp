#ifndef PASCAL_PARSER_MINIPASCAL_HPP
#define PASCAL_PARSER_MINIPASCAL_HPP

#include <boost/variant2/variant.hpp>
#include <charconv>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>

struct CharacterConstant
{
    char constant;
};

struct IntegerConstant
{
    int constant;
};

struct Identifier
{
    std::string value;
};

struct ConstantIdentifier
{
    Identifier identifier;
};

using Constant = boost::variant2::variant<IntegerConstant, CharacterConstant, ConstantIdentifier>;

struct VariableIdentifier
{
    Identifier identifier;
};

struct EntireVariable
{
    VariableIdentifier identifier;
};

struct ArrayVariable
{
    EntireVariable variable;
};

struct Expression;

struct IndexedVariable
{
    ArrayVariable array;
    std::unique_ptr<Expression> index;
};

using Variable = boost::variant2::variant<EntireVariable, IndexedVariable>;

enum class MultiplyingOperator
{
    Star,
    Div,
    And,
};

enum class AddingOperator
{
    Plus,
    Minus,
    Or,
};

struct Sign
{
    enum class Type
    {
        Positive,
        Negative,
    };
    std::optional<Type> value;
};

enum class RelationalOperator
{
    Equals,
    LessGreater,
    Less,
    LessEquals,
    GreaterEquals,
    Greater,
};

struct Factor
{
    boost::variant2::variant<Variable, Constant, std::unique_ptr<Expression>, std::unique_ptr<Factor>> value;
};

struct Term
{
    struct Rhs
    {
        MultiplyingOperator op;
        Factor factor;
    };
    Factor first;
    std::vector<Rhs> rest;
};

struct SimpleExpression
{
    struct Rhs
    {
        AddingOperator op;
        Term term;
    };
    Sign sign;
    Term first;
    std::vector<Rhs> rest;
};

struct Expression
{
    struct Rhs
    {
        RelationalOperator op;
        SimpleExpression simple_expression;
    };
    SimpleExpression lhs;
    std::optional<Rhs> rhs;
};

struct Statement;

struct WhileStatement
{
    Expression condition;
    std::unique_ptr<Statement> body;
};

struct IfStatement
{
    Expression condition;
    std::unique_ptr<Statement> body;
    std::optional<std::unique_ptr<Statement>> else_clause;
};

struct CompoundStatement
{
    std::vector<Statement> statements;
};

using StructuredStatement = boost::variant2::variant<CompoundStatement, IfStatement, WhileStatement>;

struct OutputValue
{
    Expression expression;
};

struct WriteStatement
{
    std::vector<OutputValue> output_values;
};

struct InputVariable
{
    Variable variable;
};

struct ReadStatement
{
    std::vector<InputVariable> input_variables;
};

struct ProcedureIdentifier
{
    Identifier identifier;
};

struct ProcedureStatement
{
    ProcedureIdentifier identifier;
};

struct AssignmentStatement
{
    Variable target;
    Expression value;
};

using SimpleStatement =
    boost::variant2::variant<AssignmentStatement, ProcedureStatement, ReadStatement, WriteStatement>;

struct Statement
{
    boost::variant2::variant<SimpleStatement, StructuredStatement> value;
};

struct StatementPart
{
    CompoundStatement statement;
};

struct Block;

struct ProcedureDeclaration
{
    Identifier name;
    std::unique_ptr<Block> body;
};

struct ProcedureDeclarationPart
{
    std::vector<ProcedureDeclaration> procedures;
};

struct TypeIdentifier
{
    Identifier identifier;
};

struct SimpleType
{
    TypeIdentifier identifier;
};

struct IndexRange
{
    IntegerConstant begin;
    IntegerConstant end;
};

struct ArrayType
{
    IndexRange index_range;
    SimpleType element_type;
};

using Type = boost::variant2::variant<SimpleType, ArrayType>;

struct VariableDeclaration
{
    std::vector<Identifier> identifiers;
    Type type;
};

struct VariableDeclarationPart
{
    std::vector<VariableDeclaration> variable_declarations;
};

struct Block
{
    VariableDeclarationPart variable_declaration_part;
    ProcedureDeclarationPart procedure_declaration_part;
    StatementPart statement_part;
};

struct Program
{
    Identifier name;
    Block body;
};

using MiniPascalNode =
    boost::variant2::variant<CharacterConstant, IntegerConstant, Identifier, ConstantIdentifier, Constant,
                             VariableIdentifier, EntireVariable, ArrayVariable, IndexedVariable, Variable,
                             MultiplyingOperator, AddingOperator, Sign, RelationalOperator, Factor, Term,
                             SimpleExpression, Expression, CompoundStatement, WhileStatement, IfStatement,
                             StructuredStatement, OutputValue, WriteStatement, InputVariable, ReadStatement,
                             ProcedureIdentifier, ProcedureStatement, AssignmentStatement, SimpleStatement, Statement,
                             StatementPart, ProcedureDeclaration, ProcedureDeclarationPart, TypeIdentifier, SimpleType,
                             IndexRange, ArrayType, Type, VariableDeclaration, VariableDeclarationPart, Block, Program>;

#define D_ParseNode_User MiniPascalNode

#endif // PASCAL_PARSER_MINIPASCAL_HPP
