{
#include "pascal_nodes.hpp"
}
${declare save_parse_tree}

program: program_heading block '.'
    ;

identifier_list: name 
    (
        ',' name
    )*
    ;

program_heading: 'program'/i name '(' identifier_list ')' ';'
    ;

block: declaration_part statement_part
    ;

label: number
    ;

formal_parameter_list: '(' formal_parameter_section
    (
        ';' formal_parameter_section
    )*
    ')'
    ;

formal_parameter_section: 
    (
        'var'/i
    )?
    identifier_list ':' parameter_type
    ;

parameter_type: type_name
    ;

constant:
    (
        (
            '+'
            |
            '-'
        )?
        constant_name
        |
        number
    )
    |
    string
    ;

case_label_list: constant
    (
        ',' constant
    )*
    ;

type: simple_type
    |
    structured_type
    |
    pointer_type
    |
    procedural_type
    |
    type_name
    ;

simple_type: subrange_type
    |
    enumerated_type
    ;

subrange_type: constant '..' constant
    ;

enumerated_type: '(' identifier_list ')'
    ;

structured_type:
    (
        'packed'/i
    )?
    unpacked_structured_type
    ;

unpacked_structured_type: array_type
    |
    record_type
    |
    set_type
    |
    file_type
    ;

array_type: 'array'/i '[' index_type
    (
        ',' index_type
    )*
    ']' 'of'/i element_type
    ;

index_type: simple_type
    ;

element_type: type
    ;

record_type: 'record'/i field_list 'end'/i
    ;

field_list:
    (
        (
            fixed_part
            (
                ';' variant_part
            )?
            |
            variant_part
        )
        ';'?
    )?
    ;

fixed_part: record_section
    (
        ';' record_section
    )*
    ;

record_section: identifier_list ':' type
    ;

variant_part: 'case'/i tag_field type_name 'of'/i variant
    (
        ';' variant
    )*
    ;

tag_field:
    (
        name ':'
    )?
    ;

variant: case_label_list ':' '(' field_list ')'
    ;

set_type: 'set'/i 'of'/i base_type
    ;

base_type: type
    ;

file_type: 'file'/i
    (
        'of'/i file_component_type
    )?
    ;

file_component_type: type
    ;

pointer_type: '^' type_name
    ;

procedural_type: procedure_type
    |
    function_type
    ;

procedure_type: 'procedure'/i
    (
        formal_parameter_list
    )?
    ;

function_type: 'function'/i
    (
        formal_parameter_list
    )?
    ':' type_name
    ;

declaration_part:
    (
        label_declaration_part
        |
        constant_definition_part
        |
        type_definition_part
        |
        variable_declaration_part
        |
        procedure_and_function_declaration_part
    )*
    ;

label_declaration_part: 'label'/i label
    (
        ',' label
    )*
    ';'
    ;

constant_definition_part: 'const'/i constant_definition ';'
    (
        constant_definition ';'
    )*
    ;

constant_definition: name '=' constant
    ;

type_definition_part: 'type'/i type_definition ';'
    (
        type_definition ';'
    )*
    ;

type_definition: name '=' type
    ;

variable_declaration_part: 'var'/i variable_declaration ';'
    (
        variable_declaration ';'
    )*
    ;

variable_declaration: identifier_list ':' type
    ;

procedure_and_function_declaration_part:
    (
        procedure_declaration
        |
        function_declaration
    )
    ';'
    ;

directive: 'forward'/i
    ;

procedure_declaration: procedure_heading ';'
    (
        block
        |
        directive
    )
    ;

procedure_heading: 'procedure'/i name
    (
        formal_parameter_list
    )?
    ;

function_declaration: function_heading ';'
    (
        block
        |
        directive
    )
    ;

function_heading: 'function'/i name
    (
        formal_parameter_list
    )?
    ':' type_name
    ;

statement_part: 'begin'/i statement_sequence 'end'/i
    ;

statement_sequence: statement
    (
        ';' statement
    )*
    ;

expression_list: expression
    (
        ',' expression
    )*
    ;

variable_access: access_name
    (
        end_access
    )*
    ;

end_access:
    (
        array_access
        |
        record_access
        |
        '^'
        |
        function_parameters
    )*
    ;

array_access: '[' expression_list ']'
    ;

record_access: '.' variable_access
    ;

function_parameters: '('
    (
        expression_list
    )?
    ')'
    ;

actual_parameter_list: '(' actual_parameter
    (
        ',' actual_parameter
    )*
    ')'
    ;

actual_parameter: actual_value
    |
    actual_variable
    |
    actual_procedure
    |
    actual_function
    ;

actual_procedure: procedure_name
    ;

actual_function: function_name
    ;

actual_value: expression
    ;

actual_variable: variable_access
    ;

expression: simple_expression
    (
        relational_operator simple_expression
    )?
    ;

relational_operator: '='
    |
    '<>'
    |
    '<'
    |
    '<='
    |
    '>'
    |
    '>='
    |
    'in'/i
    ;

simple_expression:
    (
        '+'
        |
        '-'
    )?
    term
    (
        addition_operator term
    )*
    ;

addition_operator: '+'
    |
    '-'
    |
    'or'/i
    ;

term: factor
    (
        multiplication_operator factor
    )*
    ;

multiplication_operator: '*'
    |
    '/'
    |
    'div'/i
    |
    'mod'/i
    |
    'and'/i
    ;

factor: number 
    | 
    string 
    | 
    'nil'/i 
    | 
    constant_name 
    | 
    set
    |
    variable_access
    |
    function_designator
    |
    '(' expression ')'
    |
    'not'/i factor
    ;

function_designator: function_name
    (
        actual_parameter_list
    )?
    ;

set: '[' element_list ']'
    ;

element_list:
    (
        expression
        (
            ',' expression
        )*
    )?
    ;

statement:
    (
        'label'/i ':'
    )?
    (
        simple_statement
        |
        structured_statement
    )
    ;

simple_statement:
    (
        assignment_statement
        |
        procedure_statement
        |
        goto_statement
    )?
    ;

assignment_statement:
    (
        variable_access
        |
        function_name
    )
    ':=' expression
    ;

procedure_statement: procedure_name
    (
        actual_parameter_list
    )?
    ;

goto_statement: 'goto'/i label
    ;

structured_statement: compound_statement
    |
    repetitive_statement
    |
    conditional_statement
    |
    with_statement
    ;

compound_statement: 'begin'/i statement_sequence 'end'/i
    ;

repetitive_statement: while_statement
    |
    repeat_statement
    |
    for_statement
    ;

while_statement: 'while'/i expression 'do'/i statement
    ;

repeat_statement: 'repeat'/i statement_sequence 'until'/i expression
    ;

for_statement: 'for'/i variable_name ':=' initial_expression
    (
        'to'/i
        |
        'downto'/i
    )
    final_expression 'do'/i statement
    ;

initial_expression: expression
    ;

final_expression: expression
    ;

conditional_statement: if_statement
    |
    case_statement
    ;

if_statement: 'if'/i expression 'then'/i statement
    (
        'else'/i statement
    )?
    ;

case_statement: 'case'/i expression 'of'/i case_element
    (
        ';' case_element
    )*
    ';'? 'end'/i
    ;

case_element: case_label_list ':' statement
    ;

with_statement: 'with'/i variable_access
    (
        ',' variable_access
    )*
    'do'/i statement
    ;

name: "[a-zA-Z_][a-zA-Z0-9_]*"
    ;

number: "[0-9]+"
    ;

type_name: 'integer'/i
    |
    'real'/i
    ;

string: "'([^']|'')*'"
    ;

constant_name: name
    ;

access_name: name
    ;

procedure_name: name
    ;

function_name: name
    ;

variable_name: name
    ;
