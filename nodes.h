#ifndef PASCAL_NODES_H
#define PASCAL_NODES_H

#include "vec.h"

enum node_type
{
    node_program,
    node_identifier_list,
    node_declarations,
    node_type,
    node_subprogram_declarations,
    node_subprogram_declaration,
    node_function_head,
    node_procedure_head,
    node_subprogram_head,
    node_parameter_list,
    node_statement_list,
    node_while_statement,
    node_if_statement,
    node_compound_statement,
    node_assignment_statement,
    node_statement,
    node_variable,
    node_procedure_statement,
    node_expression_list,
    node_expression,
    node_simple_expression,
    node_factor,
    node_term,
    node_id,
    node_standard_type,
};

enum factor_type
{
    factor_id,
    factor_call,
    factor_num,
    factor_parenthesized_expression,
    factor_not,
};

enum mulop
{
    mulop_multiply,
    mulop_divide,
    mulop_div,
    mulop_mod,
    mulop_and,
};

enum simple_expression_type
{
    simple_expression_terms,
    simple_expression_signed,
};

enum sign
{
    sign_positive,
    sign_negative,
};

enum relop
{
    relop_less,
    relop_less_equal,
    relop_greater,
    relop_greater_equal,
    relop_equal,
    relop_not_equal,
};

enum statement_type
{
    statement_assignment,
    statement_procedure,
    statement_compound,
    statement_if,
    statement_while,
};

enum subprogram_head_type
{
    subprogram_head_function,
    subprogram_head_procedure,
};

enum standard_type
{
    standard_type_integer,
    standard_type_real,
};

enum type_type
{
    type_standard,
    type_array,
};

struct program
{
    char *id;
    struct identifier_list *parameters;
    struct declarations *declarations;
    struct subprogram_declarations *subprogram_declarations;
    struct compound_statement *body;
};

struct identifier_list
{
    vec_str_t identifiers;
};

struct declarations
{
    vec_t(struct declaration {
        struct identifier_list *identifiers;
        struct type *type;
    }) declarations;
};

struct array_type
{
    char *low;
    char *high;
    enum standard_type element_type;
};

struct type
{
    enum type_type t;
    union {
        enum standard_type standard;
        struct array_type *array;
    } u;
};

struct subprogram_declarations
{
    vec_t(struct subprogram_declaration *) declarations;
};

struct subprogram_declaration
{
    struct subprogram_head *head;
    struct declarations *declarations;
    struct compound_statement *body;
};

struct procedure_head
{
    char *id;
    struct parameter_list *parameters;
};

struct function_head
{
    char *id;
    struct parameter_list *parameters;
    enum standard_type type;
};

struct subprogram_head
{
    enum subprogram_head_type t;
    union {
        struct function_head *function;
        struct procedure_head *procedure;
    } u;
};

struct typed_identifier_list
{
    struct identifier_list *identifiers;
    struct type *type;
};

struct parameter_list
{
    struct typed_identifier_list *first;
    vec_t(struct typed_identifier_list *) rest;
};

struct compound_statement
{
    struct statement_list *statements;
};

struct statement_list
{
    vec_t(struct statement *) statements;
};

struct if_statement
{
    struct expression *condition;
    struct statement *then_branch;
    struct statement *else_branch;
};

struct while_statement
{
    struct expression *condition;
    struct statement *body;
};

struct assignment_statement
{
    struct variable *variable;
    struct expression *value;
};

struct statement
{
    enum statement_type t;
    union {
        struct assignment_statement *assignment;
        struct procedure_statement *procedure;
        struct compound_statement *compound;
        struct if_statement *ifs;
        struct while_statement *whiles;
    } u;
};

struct variable
{
    char *id;
    struct expression *index;
};

struct procedure_statement
{
    struct call *call;
};

struct expression_list
{
    vec_t(struct expression *) expressions;
};

struct expression_rhs
{
    enum relop op;
    struct simple_expression *simple_expression;
};

struct expression
{
    struct simple_expression *first;
    vec_t(struct expression_rhs *) rest;
};

struct call
{
    char *id;
    struct expression_list *arguments;
};

struct simple_expression
{
    enum simple_expression_type t;
    struct term *term;
    union {
        vec_t(struct simple_expression_rhs *) rest;
        enum sign sign;
    } u;
};

struct term_rhs
{
    enum mulop op;
    struct factor *rhs;
};

struct term
{
    struct factor *first;
    vec_t(struct term_rhs *) rest;
};

struct factor
{
    enum factor_type t;
    union {
        char *id;
        struct call *call;
        char *num;
        struct expression *parenthesized_expression;
        struct factor *not_factor;
    } u;
};

typedef struct
{
    enum node_type t;
    union {
        struct program *program;
        struct identifier_list *identifier_list;
        struct declarations *declarations;
        struct type *type;
        struct subprogram_declarations *subprogram_declarations;
        struct subprogram_declaration *subprogram_declaration;
        struct function_head *function_head;
        struct procedure_head *procedure_head;
        struct subprogram_head *subprogram_head;
        struct parameter_list *parameter_list;
        struct statement_list *statement_list;
        struct while_statement *while_statement;
        struct if_statement *if_statement;
        struct compound_statement *compound_statement;
        struct assignment_statement *assignment_statement;
        struct statement *statement;
        struct variable *variable;
        struct procedure_statement *procedure_statement;
        struct expression_list *expression_list;
        struct expression *expression;
        struct simple_expression *simple_expression;
        struct factor *factor;
        struct term *term;
        char *id;
        enum standard_type standard_type;
    } u;
} My_ParseNode;

#define D_ParseNode_User My_ParseNode

#endif // PASCAL_NODES_H
