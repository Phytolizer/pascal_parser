#include "nodes.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

extern "C"
{
#include "dparse.hpp"
}

extern D_ParserTables parser_tables_pascal;

int main(int argc, char *argv[])
{
    auto *parser = new_D_Parser(&parser_tables_pascal, sizeof(D_ParseNode_User));
    parser->save_parse_tree = true;

    std::string buf;
    std::string source;
    while (std::getline(std::cin, buf))
    {
        source += "\n" + buf;
    }
    auto *pn = dparse(parser, source.data(), source.length());
    if (!pn || parser->syntax_errors > 0)
    {
        std::cerr << ":(\n";
        exit(1);
    }
}
