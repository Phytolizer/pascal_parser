#include "nodes.h"
#include <dparse.h>
#include <dparse_tables.h>
#include <dsymtab.h>
#include <stdio.h>
#include <stdlib.h>

extern D_ParserTables parser_tables_gram;

int main(int argc, char *argv[])
{
    D_Parser *p = new_D_Parser(&parser_tables_gram, sizeof(My_ParseNode));
    p->save_parse_tree = 1;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        perror("fopen");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc(len + 1);
    if (fread(buf, 1, len, f) != len)
    {
        perror("fread");
        exit(1);
    }
    buf[len] = '\0';
    D_ParseNode *pn = dparse(p, buf, len);
    if (!pn || p->syntax_errors)
    {
        fprintf(stderr, "parse failed\n");
        exit(1);
    }

    printf("%d\n", pn->symbol);
    for (int i = 0; i < d_get_number_of_children(pn); i++)
    {
        printf("%d\n", d_get_child(pn, i)->user.t);
    }
}
