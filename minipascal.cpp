#include "minipascal.hpp"
#include <dparse.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <sstream>
#include <string>

extern D_ParserTables parser_tables_minipascal;

int main(int argc, char *argv[])
{
    D_Parser *parser = new_D_Parser(&parser_tables_minipascal, sizeof(D_ParseNode_User));
    parser->save_parse_tree = true;

    std::string buf;
    std::stringstream sourceStream;
    while (std::getline(std::cin, buf))
    {
        fmt::print(sourceStream, "{}\n", buf);
    }
    std::string source = sourceStream.str();

    auto *parseNode = dparse(parser, source.data(), source.size());

    if (!parseNode || parser->syntax_errors > 0)
    {
        fmt::print(std::cerr, "Syntax error :(\n");
        exit(1);
    }

    free_D_Parser(parser);
}
