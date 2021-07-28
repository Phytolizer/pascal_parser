#ifndef PASCAL_PARSER_MINIPASCAL_HPP
#define PASCAL_PARSER_MINIPASCAL_HPP

#include <boost/variant2/variant.hpp>
#include <charconv>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <type_traits>
#include <vector>

struct CharacterConstant
{
    char constant;
};

std::ostream &operator<<(std::ostream &os, const CharacterConstant &cc);

struct IntegerConstant
{
    int constant;
};

std::ostream &operator<<(std::ostream &os, const IntegerConstant &ic);

struct Identifier
{
    std::string value;
};

std::ostream &operator<<(std::ostream &os, const Identifier &i);

struct ConstantIdentifier
{
    Identifier identifier;
};

std::ostream &operator<<(std::ostream &os, const ConstantIdentifier &ci);

using Constant = boost::variant2::variant<IntegerConstant, CharacterConstant, ConstantIdentifier>;

std::ostream &operator<<(std::ostream &os, const Constant &c);

struct VariableIdentifier
{
    Identifier identifier;
};

std::ostream &operator<<(std::ostream &os, const VariableIdentifier &vi);

struct EntireVariable
{
    VariableIdentifier identifier;
};

std::ostream &operator<<(std::ostream &os, const EntireVariable &ev);

struct ArrayVariable
{
    EntireVariable variable;
};

std::ostream &operator<<(std::ostream &os, const ArrayVariable &av);

struct Expression;
std::ostream &operator<<(std::ostream &os, const Expression &e);

struct IndexedVariable
{
    ArrayVariable array;
    std::unique_ptr<Expression> index;
};

std::ostream &operator<<(std::ostream &os, const IndexedVariable &iv);

using Variable = boost::variant2::variant<EntireVariable, IndexedVariable>;

std::ostream &operator<<(std::ostream &os, const Variable &v);

enum class MultiplyingOperator
{
    Star,
    Div,
    And,
};

std::ostream &operator<<(std::ostream &os, const MultiplyingOperator &mo);

enum class AddingOperator
{
    Plus,
    Minus,
    Or,
};

std::ostream &operator<<(std::ostream &os, const AddingOperator &ao);

struct Sign
{
    enum class Type
    {
        Positive,
        Negative,
    };
    std::optional<Type> value;
};

std::ostream &operator<<(std::ostream &os, const Sign &s);

enum class RelationalOperator
{
    Equals,
    LessGreater,
    Less,
    LessEquals,
    GreaterEquals,
    Greater,
};

std::ostream &operator<<(std::ostream &os, const RelationalOperator &ro);

struct Factor
{
    boost::variant2::variant<Variable, Constant, std::unique_ptr<Expression>, std::unique_ptr<Factor>> value;
};

std::ostream &operator<<(std::ostream &os, const Factor &f);

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

std::ostream &operator<<(std::ostream &os, const Term::Rhs &rhs);

std::ostream &operator<<(std::ostream &os, const Term &t);

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

std::ostream &operator<<(std::ostream &os, const SimpleExpression::Rhs &rhs);

std::ostream &operator<<(std::ostream &os, const SimpleExpression &se);

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

std::ostream &operator<<(std::ostream &os, const Expression::Rhs &rhs);

struct Statement;
std::ostream &operator<<(std::ostream &os, const Statement &s);

struct WhileStatement
{
    Expression condition;
    std::unique_ptr<Statement> body;
};

std::ostream &operator<<(std::ostream &os, const WhileStatement &ws);

struct IfStatement
{
    Expression condition;
    std::unique_ptr<Statement> body;
    std::optional<std::unique_ptr<Statement>> else_clause;
};

std::ostream &operator<<(std::ostream &os, const IfStatement &is);

struct CompoundStatement
{
    std::vector<Statement> statements;
};

std::ostream &operator<<(std::ostream &os, const CompoundStatement &cs);

using StructuredStatement = boost::variant2::variant<CompoundStatement, IfStatement, WhileStatement>;

std::ostream &operator<<(std::ostream &os, const StructuredStatement &ss);

struct OutputValue
{
    Expression expression;
};

std::ostream &operator<<(std::ostream &os, const OutputValue &ov);

struct WriteStatement
{
    std::vector<OutputValue> output_values;
};

std::ostream &operator<<(std::ostream &os, const WriteStatement &ws);

struct InputVariable
{
    Variable variable;
};

std::ostream &operator<<(std::ostream &os, const InputVariable &iv);

struct ReadStatement
{
    std::vector<InputVariable> input_variables;
};

std::ostream &operator<<(std::ostream &os, const ReadStatement &rs);

struct ProcedureIdentifier
{
    Identifier identifier;
};

std::ostream &operator<<(std::ostream &os, const ProcedureIdentifier &pi);

struct ProcedureStatement
{
    ProcedureIdentifier identifier;
};

std::ostream &operator<<(std::ostream &os, const ProcedureStatement &ps);

struct AssignmentStatement
{
    Variable target;
    Expression value;
};

std::ostream &operator<<(std::ostream &os, const AssignmentStatement &as);

using SimpleStatement =
    boost::variant2::variant<AssignmentStatement, ProcedureStatement, ReadStatement, WriteStatement>;

std::ostream &operator<<(std::ostream &os, const SimpleStatement &ss);

struct Statement
{
    boost::variant2::variant<SimpleStatement, StructuredStatement> value;
};

struct StatementPart
{
    CompoundStatement statement;
};

std::ostream &operator<<(std::ostream &os, const StatementPart &sp);

struct Block;
std::ostream &operator<<(std::ostream &os, const Block &b);

struct ProcedureDeclaration
{
    Identifier name;
    std::unique_ptr<Block> body;
};

std::ostream &operator<<(std::ostream &os, const ProcedureDeclaration &pd);

struct ProcedureDeclarationPart
{
    std::vector<ProcedureDeclaration> procedures;
};

std::ostream &operator<<(std::ostream &os, const ProcedureDeclarationPart &pdp);

struct TypeIdentifier
{
    Identifier identifier;
};

std::ostream &operator<<(std::ostream &os, const TypeIdentifier &ti);

struct SimpleType
{
    TypeIdentifier identifier;
};

std::ostream &operator<<(std::ostream &os, const SimpleType &st);

struct IndexRange
{
    IntegerConstant begin;
    IntegerConstant end;
};

std::ostream &operator<<(std::ostream &os, const IndexRange &ir);

struct ArrayType
{
    IndexRange index_range;
    SimpleType element_type;
};

std::ostream &operator<<(std::ostream &os, const ArrayType &at);

using Type = boost::variant2::variant<SimpleType, ArrayType>;

std::ostream &operator<<(std::ostream &os, const Type &t);

struct VariableDeclaration
{
    std::vector<Identifier> identifiers;
    Type type;
};

std::ostream &operator<<(std::ostream &os, const VariableDeclaration &vd);

struct VariableDeclarationPart
{
    std::vector<VariableDeclaration> variable_declarations;
};

std::ostream &operator<<(std::ostream &os, const VariableDeclarationPart &vdp);

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

std::ostream &operator<<(std::ostream &os, const Program &p);

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
