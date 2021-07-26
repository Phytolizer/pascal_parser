{
#include "minipascal.hpp"
using namespace boost::variant2;
}
${declare save_parse_tree}

program: 
    'program'/i identifier ';' block '.'
    {
        $$ = Program{
            .name = std::move(*get_if<Identifier>(&$1)),
            .body = std::move(*get_if<Block>(&$3)),
        };
    }
    ;

block: 
    variable_declaration_part procedure_declaration_part statement_part
    {
        $$ = Block{
            .variable_declaration_part = std::move(*get_if<VariableDeclarationPart>(&$0)),
            .procedure_declaration_part = std::move(*get_if<ProcedureDeclarationPart>(&$1)),
            .statement_part = std::move(*get_if<StatementPart>(&$2)),
        };
    }
    ;

variable_declaration_part:
    (
        'var' variable_declaration ';'
        {
            $$ = VariableDeclarationPart{ .variable_declarations = {std::move(*get_if<VariableDeclaration>(&$1))} };
        }
        (
            variable_declaration ';'
            {
                get_if<VariableDeclarationPart>(&$$)->variable_declarations.emplace_back(std::move(*get_if<VariableDeclaration>(&$0)));
            }
        )*
    )?
    {
        if ($# == -1)
        {
            $$ = VariableDeclarationPart{};
        }
    }
    ;

variable_declaration: 
    identifier
    (
        ',' identifier
        {
            get_if<VariableDeclaration>(&$$)->identifiers.emplace_back(std::move(*get_if<Identifier>(&$1)));
        }
    )*
    ':' type
    {
        $$ = VariableDeclaration{
            .identifiers = {std::move(*get_if<Identifier>(&$0))},
            .type = std::move(*get_if<Type>(&$3)),
        };
    }
    ;

type: 
    simple_type
    {
        $$ = Type{std::move(*get_if<SimpleType>(&$0))};
    }
    |
    array_type
    {
        $$ = Type{std::move(*get_if<ArrayType>(&$0))};
    }
    ;

array_type: 
    'array'/i '[' index_range ']' 'of'/i simple_type
    {
        $$ = ArrayType{
            .index_range = std::move(*get_if<IndexRange>(&$2)),
            .element_type = std::move(*get_if<SimpleType>(&$5)),
        };
    }
    ;

index_range: 
    integer_constant '..' integer_constant
    {
        $$ = IndexRange{
            .begin = std::move(*get_if<IntegerConstant>(&$0)),
            .end = std::move(*get_if<IntegerConstant>(&$2)),
        };
    }
    ;

simple_type: 
    type_identifier
    {
        $$ = SimpleType{ .identifier = *get_if<TypeIdentifier>(&$0) };
    }
    ;

type_identifier: 
    identifier
    {
        $$ = TypeIdentifier{ .identifier = *get_if<Identifier>(&$0) };
    }
    ;

procedure_declaration_part:
    (
        procedure_declaration ';'
        {
            if (!get_if<ProcedureDeclarationPart>(&$$))
            {
                $$ = ProcedureDeclarationPart{ .procedures = {} };
            }
            get_if<ProcedureDeclarationPart>(&$$)->procedures.emplace_back(std::move(*get_if<ProcedureDeclaration>(&$0)));
        }
    )*
    ;

procedure_declaration: 
    'procedure'/i identifier ';' block
    {
        $$ = ProcedureDeclaration{ 
            .name = *get_if<Identifier>(&$1),
            .body = std::make_unique<Block>(std::move(*get_if<Block>(&$3))),
        };
    }
    ;

statement_part: 
    compound_statement
    {
        $$ = StatementPart{ .statement = std::move(*get_if<CompoundStatement>(&$0)) };
    }
    ;

compound_statement: 
    'begin'/i statement
    (
        ';' statement
        {
            get_if<CompoundStatement>(&$$)->statements.emplace_back(std::move(*get_if<Statement>(&$1)));
        }
    )*
    'end'/i
    {
        $$ = CompoundStatement{};
        get_if<CompoundStatement>(&$$)->statements.emplace_back(std::move(*get_if<Statement>(&$1)));
    }
    ;

statement: 
    simple_statement
    {
        $$ = Statement{std::move(*get_if<SimpleStatement>(&$0))};
    }
    |
    structured_statement
    {
        $$ = Statement{std::move(*get_if<StructuredStatement>(&$0))};
    }
    ;

simple_statement:
    assignment_statement
    {
        $$ = SimpleStatement{std::move(*get_if<AssignmentStatement>(&$0))};
    }
    |
    procedure_statement
    {
        $$ = SimpleStatement{std::move(*get_if<ProcedureStatement>(&$0))};
    }
    |
    read_statement
    {
        $$ = SimpleStatement{std::move(*get_if<ReadStatement>(&$0))};
    }
    |
    write_statement
    {
        $$ = SimpleStatement{std::move(*get_if<WriteStatement>(&$0))};
    }
    ;

assignment_statement:
    variable ':=' expression
    {
        $$ = AssignmentStatement{ 
            .target = std::move(*get_if<Variable>(&$0)),
            .value = std::move(*get_if<Expression>(&$2)),
        };
    }
    ;

procedure_statement:
    procedure_identifier
    {
        $$ = ProcedureStatement{ .identifier = *get_if<ProcedureIdentifier>(&$0) };
    }
    ;

procedure_identifier:
    identifier
    {
        $$ = ProcedureIdentifier{ .identifier = *get_if<Identifier>(&$0) };
    }
    ;

read_statement: 
    'read'/i '(' input_variable
    (
        ',' input_variable
        {
            get_if<ReadStatement>(&$$)->input_variables.emplace_back(std::move(*get_if<InputVariable>(&$1)));
        }
    )*
    ')'
    {
        $$ = ReadStatement{};
        get_if<ReadStatement>(&$$)->input_variables.emplace_back(std::move(*get_if<InputVariable>(&$2)));
    }
    ;

input_variable:
    variable
    {
        $$ = InputVariable{ .variable = std::move(*get_if<Variable>(&$0)) };
    }
    ;

write_statement:
    'write'/i '(' output_value
    (
        ',' output_value
        {
            get_if<WriteStatement>(&$$)->output_values.emplace_back(std::move(*get_if<OutputValue>(&$1)));
        }
    )*
    ')'
    {
        $$ = WriteStatement{};
        get_if<WriteStatement>(&$$)->output_values.emplace_back(std::move(*get_if<OutputValue>(&$2)));
    }
    ;

output_value:
    expression
    {
        $$ = OutputValue{ .expression = std::move(*get_if<Expression>(&$0)) };
    }
    ;

structured_statement:
    compound_statement
    {
        $$ = StructuredStatement{std::move(*get_if<CompoundStatement>(&$0))};
    }
    |
    if_statement
    {
        $$ = StructuredStatement{std::move(*get_if<IfStatement>(&$0))};
    }
    |
    while_statement
    {
        $$ = StructuredStatement{std::move(*get_if<WhileStatement>(&$0))};
    }
    ;

if_statement:
    'if'/i expression 'then'/i statement
    {
        $$ = IfStatement{
            .condition = std::move(*get_if<Expression>(&$1)),
            .body = std::make_unique<Statement>(std::move(*get_if<Statement>(&$3))),
            .else_clause = {},
        };
    }
    |
    'if'/i expression 'then'/i statement 'else'/i statement
    {
        $$ = IfStatement{
            .condition = std::move(*get_if<Expression>(&$1)),
            .body = std::make_unique<Statement>(std::move(*get_if<Statement>(&$3))),
            .else_clause = std::make_unique<Statement>(std::move(*get_if<Statement>(&$5))),
        };
    }
    ;

while_statement: 
    'while'/i expression 'do'/i statement
    {
        $$ = WhileStatement{
            .condition = std::move(*get_if<Expression>(&$1)),
            .body = std::make_unique<Statement>(std::move(*get_if<Statement>(&$3))),
        };
    }
    ;

expression:
    simple_expression
    {
        $$ = Expression{ .lhs = std::move(*get_if<SimpleExpression>(&$0)) };
    }
    |
    simple_expression relational_operator simple_expression
    {
        $$ = Expression{ 
            .lhs = std::move(*get_if<SimpleExpression>(&$0)), 
            .rhs = Expression::Rhs{
                .op = *get_if<RelationalOperator>(&$1),
                .simple_expression = std::move(*get_if<SimpleExpression>(&$2)),
            },
        };
    }
    ;

simple_expression: 
    sign term
    (
        adding_operator term
        {
            get_if<SimpleExpression>(&$$)->rest.emplace_back(SimpleExpression::Rhs{ .op = *get_if<AddingOperator>(&$0), .term = std::move(*get_if<Term>(&$1)) });
        }
    )*
    {
        $$ = SimpleExpression{
            .sign = std::move(*get_if<Sign>(&$0)),
            .first = std::move(*get_if<Term>(&$1))
        };
    }
    ;

term:
    factor
    (
        multiplying_operator factor
        {
            get_if<Term>(&$$)->rest.emplace_back(Term::Rhs{ .op = *get_if<MultiplyingOperator>(&$0), .factor = std::move(*get_if<Factor>(&$1)) });
        }
    )*
    {
        $$ = Term{ .first = std::move(*get_if<Factor>(&$0)) };
    }
    ;

factor:
    variable
    {
        $$ = Factor{ .value = std::move(*get_if<Variable>(&$0)) };
    }
    |
    constant
    {
        $$ = Factor{ .value = std::move(*get_if<Constant>(&$0)) };
    }
    |
    '(' expression ')'
    {
        $$ = Factor{ .value = std::make_unique<Expression>(std::move(*get_if<Expression>(&$1))) };
    }
    |
    'not'/i factor
    {
        $$ = Factor{ .value = std::make_unique<Factor>(std::move(*get_if<Factor>(&$1))) };
    }
    ;

relational_operator:
    '='
    {
        $$ = RelationalOperator::Equals;
    }
    |
    '<>'
    {
        $$ = RelationalOperator::LessGreater;
    }
    |
    '<'
    {
        $$ = RelationalOperator::Less;
    }
    |
    '<='
    {
        $$ = RelationalOperator::LessEquals;
    }
    |
    '>='
    {
        $$ = RelationalOperator::GreaterEquals;
    }
    |
    '>'
    {
        $$ = RelationalOperator::Greater;
    }
    ;

sign:
    (
        '+'
        {
            $$ = Sign{ .value = Sign::Type::Positive };
        }
        |
        '-'
        {
            $$ = Sign{ .value = Sign::Type::Negative };
        }
    )?
    {
        if ($# == 0)
        {
            $$ = Sign{ .value = {} };
        }
    }
    ;

adding_operator:
    '+'
    {
        $$ = AddingOperator::Plus;
    }
    |
    '-'
    {
        $$ = AddingOperator::Minus;
    }
    |
    'or'/i
    {
        $$ = AddingOperator::Or;
    }
    ;

multiplying_operator:
    '*'
    {
        $$ = MultiplyingOperator::Star;
    }
    |
    'div'/i
    {
        $$ = MultiplyingOperator::Div;
    }
    |
    'and'/i
    {
        $$ = MultiplyingOperator::And;
    }
    ;

variable:
    entire_variable
    {
        $$ = Variable{std::move(*get_if<EntireVariable>(&$0))};
    }
    |
    indexed_variable
    {
        $$ = Variable{std::move(*get_if<IndexedVariable>(&$0))};
    }
    ;

indexed_variable:
    array_variable '[' expression ']'
    {
        $$ = IndexedVariable{
            .array = *get_if<ArrayVariable>(&$0),
            .index = std::make_unique<Expression>(std::move(*get_if<Expression>(&$2))),
        };
    }
    ;

array_variable:
    entire_variable
    {
        $$ = ArrayVariable{ .variable = *get_if<EntireVariable>(&$0) };
    }
    ;

entire_variable:
    variable_identifier
    {
        $$ = EntireVariable{ .identifier = *get_if<VariableIdentifier>(&$0) };
    }
    ;

variable_identifier:
    identifier
    {
        $$ = VariableIdentifier{ .identifier = *get_if<Identifier>(&$0) };
    }
    ;

constant: 
    integer_constant
    {
        $$ = Constant{std::move(*get_if<IntegerConstant>(&$0))};
    }
    |
    character_constant
    {
        $$ = Constant{std::move(*get_if<CharacterConstant>(&$0))};
    }
    |
    constant_identifier
    {
        $$ = Constant{std::move(*get_if<ConstantIdentifier>(&$0))};
    }
    ;

constant_identifier: 
    identifier
    {
        $$ = ConstantIdentifier { .identifier = *get_if<Identifier>(&$0) };
    }
    ;

identifier: 
    letter
    (
        letter
        |
        digit
    )*
    {
        $$ = Identifier { .value = std::string{$n.start_loc.s, $n.end} };
    }
    ;

integer_constant: 
    digit+
    {
        int i;
        std::from_chars($n.start_loc.s, $n.end, i);
        $$ = IntegerConstant{ .constant = i };
    }
    ;

character_constant: 
    "'[^']'"
    {
        $$ = CharacterConstant{ .constant = $n.start_loc.s[1] };
    }
    |
    '\'\'\'\''
    {
        $$ = CharacterConstant{ .constant = '\'' };
    }
    ;

letter: "[a-zA-Z]"
    ;

digit: "[0-9]"
    ;
