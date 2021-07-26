{
    #include "nodes.h"
}

program: 'program'/i id '(' identifier_list ')' ';'
    declarations?
    subprogram_declarations?
    compound_statement
    '.'
    {
        $$.t = node_program;
        $$.u.program = malloc(sizeof(struct program));
        $$.u.program->id = $2.u.id;
        $$.u.program->parameters = $4.u.identifier_list;
        $$.u.program->declarations = $7.u.declarations;
        $$.u.program->subprogram_declarations = $8.u.subprogram_declarations;
        $$.u.program->body = $9.u.compound_statement;
    }
    ;

identifier_list: id 
    {
        $$.t = node_identifier_list;
        $$.u.identifier_list = malloc(sizeof(struct identifier_list));
        vec_init(&$$.u.identifier_list->identifiers);
        vec_push(&$$.u.identifier_list->identifiers, $1.u.id);
    }
    (
        ',' id
        {
            vec_push(&$$.u.identifier_list->identifiers, $2.u.id);
        }
    )*
    ;

declarations: 'var'/i identifier_list ':' type ';'
    {
        $$.t = node_declarations;
        $$.u.declarations = malloc(sizeof(struct declarations));
        vec_init(&$$.u.declarations->declarations);
        struct declaration first = {
            .identifiers = $2.u.identifier_list,
            .type = $4.u.type,
        };
        vec_push(&$$.u.declarations->declarations, first);
    }
    (
        'var'/i identifier_list ':' type ';'
        {
            struct declaration next = {
                .identifiers = $2.u.identifier_list,
                .type = $4.u.type,
            };
            vec_push(&$$.u.declarations->declarations, next);
        }
    )*
    ;

type: standard_type
    {
        $$.t = node_type;
        $$.u.type = malloc(sizeof(struct type));
        $$.u.type->t = type_standard;
        $$.u.type->u.standard = $1.u.standard_type;
    }
    | 'array'/i '[' num '..' num ']' 'of'/i standard_type
    {
        $$.t = node_type;
        $$.u.type = malloc(sizeof(struct type));
        $$.u.type->t = type_array;
        $$.u.type->u.array = malloc(sizeof(struct array_type));
        $$.u.type->u.array->low = $3.u.id;
        $$.u.type->u.array->high = $5.u.id;
        $$.u.type->u.array->element_type = $8.u.standard_type;
    }
    ;

standard_type: 'integer'/i
    {
        $$.t = node_standard_type;
        $$.u.standard_type = standard_type_integer;
    }
    | 'real'/i
    {
        $$.t = node_standard_type;
        $$.u.standard_type = standard_type_real;
    }
    ;

subprogram_declarations: subprogram_declarations ';' 
    {
        $$.t = node_subprogram_declarations;
        $$.u.subprogram_declarations = malloc(sizeof(struct subprogram_declarations));
        vec_init(&$$.u.subprogram_declarations->declarations);
        vec_push(&$$.u.subprogram_declarations->declarations, $1.u.subprogram_declaration);
    }
    (
        subprogram_declaration ';'
        {
            vec_push(&$$.u.subprogram_declarations->declarations, $1.u.subprogram_declaration);
        }
    )*
    ;

subprogram_declaration: subprogram_head declarations? compound_statement
    ;

subprogram_head: 'function'/i id arguments ':' standard_type ';'
    | 'procedure'/i id arguments ';'
    ;

arguments: ('(' parameter_list ')')?
    ;

parameter_list: identifier_list ':' type (';' identifier_list ':' type)*
    ;

compound_statement: 'begin'/i optional_statements 'end'/i
    ;

optional_statements: statement_list?
    ;

statement_list: statement (';' statement)*
    ;

statement: variable ':=' expression
    | procedure_statement
    | compound_statement
    | 'if'/i expression 'then'/i statement 'else'/i statement
    | 'while'/i expression 'do'/i statement
    ;

variable: id ('[' expression ']')?
    ;

procedure_statement: id ('(' expression_list ')')?
    ;

expression_list: expression (',' expression)*
    ;

expression: simple_expression (relop simple_expression)?
    ;

simple_expression: term (addop term)*
    | sign term
    ;

term: factor (mulop factor)*
    ;

factor: id ('(' expression_list ')')?
    | num
    | '(' expression ')'
    | 'not'/i factor
    ;

sign: '+' 
    | '-'
    ;

id: "[a-zA-Z_][a-zA-Z0-9_]*";
num: "[0-9]+";
relop: '<'
    | '>'
    | '<='
    | '>='
    | '=='
    | '<>'
    ;
addop: '+'
    | '-'
    ;

mulop: '*'
    | '/'
    | 'div'/i
    | 'mod'/i
    | 'and'/i
    ;

whitespace: "[ \t\r\n\v\f]+";
