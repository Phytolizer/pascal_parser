#include "minipascal.hpp"
#include <dparse.hpp>
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

    std::cout << *get_if<Program>(&parseNode->user) << "\n";

    free_D_Parser(parser);
}

std::ostream &operator<<(std::ostream &os, const CharacterConstant &cc)
{
    return os << "CharacterConstant('" << cc.constant << "')";
}

std::ostream &operator<<(std::ostream &os, const IntegerConstant &ic)
{
    return os << "IntegerConstant(" << ic.constant << ")";
}

std::ostream &operator<<(std::ostream &os, const Identifier &i)
{
    return os << "Identifier('" << i.value << "')";
}

std::ostream &operator<<(std::ostream &os, const ConstantIdentifier &ci)
{
    return os << "ConstantIdentifier(" << ci.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const Constant &c)
{
    switch (c.index())
    {
    case 0:
        return os << "Constant::IntegerConstant(" << *boost::variant2::get_if<IntegerConstant>(&c) << ")";
    case 1:
        return os << "Constant::CharacterConstant(" << *boost::variant2::get_if<CharacterConstant>(&c) << ")";
    case 2:
        return os << "Constant::ConstantIdentifier(" << *boost::variant2::get_if<ConstantIdentifier>(&c) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const VariableIdentifier &vi)
{
    return os << "VariableIdentifier(" << vi.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const EntireVariable &ev)
{
    return os << "EntireVariable(" << ev.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const ArrayVariable &av)
{
    return os << "ArrayVariable(" << av.variable << ")";
}

std::ostream &operator<<(std::ostream &os, const Expression &e)
{
    os << "Expression(";
    if (e.rhs)
    {
        os << "lhs : " << e.lhs << ", rhs : " << *e.rhs;
    }
    else
    {
        os << e.lhs;
    }
    return os << ")";
}

std::ostream &operator<<(std::ostream &os, const IndexedVariable &iv)
{
    return os << "IndexedVariable(array : " << iv.array << ", index : " << *iv.index << ")";
}

std::ostream &operator<<(std::ostream &os, const Variable &v)
{
    switch (v.index())
    {
    case 0:
        return os << "Variable::EntireVariable(" << *boost::variant2::get_if<EntireVariable>(&v) << ")";
    case 1:
        return os << "Variable::IndexedVariable(" << *boost::variant2::get_if<IndexedVariable>(&v) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const MultiplyingOperator &mo)
{
    switch (mo)
    {
    case MultiplyingOperator::Star:
        return os << "'*'";
    case MultiplyingOperator::Div:
        return os << "'DIV'";
    case MultiplyingOperator::And:
        return os << "'AND'";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const AddingOperator &ao)
{
    switch (ao)
    {
    case AddingOperator::Plus:
        return os << "'+'";
    case AddingOperator::Minus:
        return os << "'-'";
    case AddingOperator::Or:
        return os << "'OR'";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Sign &s)
{
    os << "Sign(";
    if (s.value)
    {
        switch (*s.value)
        {
        case Sign::Type::Positive:
            os << "'+'";
        case Sign::Type::Negative:
            os << "'-'";
        }
    }
    else
    {
        os << "None";
    }
    return os << ")";
}

std::ostream &operator<<(std::ostream &os, const RelationalOperator &ro)
{
    switch (ro)
    {
    case RelationalOperator::Equals:
        return os << "'='";
    case RelationalOperator::LessGreater:
        return os << "'<>'";
    case RelationalOperator::Less:
        return os << "'<'";
    case RelationalOperator::LessEquals:
        return os << "'<='";
    case RelationalOperator::GreaterEquals:
        return os << "'>='";
    case RelationalOperator::Greater:
        return os << "'>'";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Factor &f)
{
    switch (f.value.index())
    {
    case 0:
        return os << "Factor::Variable(" << *boost::variant2::get_if<Variable>(&f.value) << ")";
    case 1:
        return os << "Factor::Constant(" << *boost::variant2::get_if<Constant>(&f.value) << ")";
    case 2:
        return os << "Factor::Expression(" << **boost::variant2::get_if<std::unique_ptr<Expression>>(&f.value) << ")";
    case 3:
        return os << "Factor::Not(" << **boost::variant2::get_if<std::unique_ptr<Factor>>(&f.value) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const Term::Rhs &rhs)
{
    return os << "Term::Rhs(op : " << rhs.op << ", factor : " << rhs.factor << ")";
}

std::ostream &operator<<(std::ostream &os, const Term &t)
{
    os << "Term(first : " << t.first << ", rest : [ ";
    for (int i = 0; i < t.rest.size(); ++i)
    {
        os << t.rest[i];
        if (i < t.rest.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const SimpleExpression::Rhs &rhs)
{
    return os << "SimpleExpression::Rhs(op : " << rhs.op << ", term : " << rhs.term << ")";
}

std::ostream &operator<<(std::ostream &os, const SimpleExpression &se)
{
    os << "SimpleExpression(sign : " << se.sign << ", first : " << se.first << ", rest : [ ";
    for (int i = 0; i < se.rest.size(); ++i)
    {
        os << se.rest[i];
        if (i < se.rest.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const Expression::Rhs &rhs)
{
    return os << "Expression::Rhs(op : " << rhs.op << ", simple_expression : " << rhs.simple_expression << ")";
}

std::ostream &operator<<(std::ostream &os, const Statement &s)
{
    switch (s.value.index())
    {
    case 0:
        return os << "Statement::SimpleStatement(" << *boost::variant2::get_if<SimpleStatement>(&s.value) << ")";
    case 1:
        return os << "Statement::StructuredStatement(" << *boost::variant2::get_if<StructuredStatement>(&s.value)
                  << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const WhileStatement &ws)
{
    return os << "WhileStatement(condition : " << ws.condition << ", body : " << *ws.body << ")";
}

std::ostream &operator<<(std::ostream &os, const IfStatement &is)
{
    os << "IfStatement(condition : " << is.condition << ", body : " << *is.body << ", else_clause : ";
    if (is.else_clause)
    {
        os << **is.else_clause;
    }
    return os << ")";
}

std::ostream &operator<<(std::ostream &os, const CompoundStatement &cs)
{
    os << "CompoundStatement([ ";
    for (int i = 0; i < cs.statements.size(); ++i)
    {
        os << cs.statements[i];
        if (i < cs.statements.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const StructuredStatement &ss)
{
    switch (ss.index())
    {
    case 0:
        return os << "StructuredStatement::CompoundStatement(" << *boost::variant2::get_if<CompoundStatement>(&ss)
                  << ")";
    case 1:
        return os << "StructuredStatement::IfStatement(" << *boost::variant2::get_if<IfStatement>(&ss) << ")";
    case 2:
        return os << "StructuredStatement::WhileStatement(" << *boost::variant2::get_if<WhileStatement>(&ss) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const OutputValue &ov)
{
    return os << "OutputValue(" << ov.expression << ")";
}

std::ostream &operator<<(std::ostream &os, const WriteStatement &ws)
{
    os << "WriteStatement([ ";
    for (int i = 0; i < ws.output_values.size(); ++i)
    {
        os << ws.output_values[i];
        if (i < ws.output_values.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const InputVariable &iv)
{
    return os << "InputVariable(" << iv.variable << ")";
}

std::ostream &operator<<(std::ostream &os, const ReadStatement &rs)
{
    os << "ReadStatement([ ";
    for (int i = 0; i < rs.input_variables.size(); ++i)
    {
        os << rs.input_variables[i];
        if (i < rs.input_variables.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const ProcedureIdentifier &pi)
{
    return os << "ProcedureIdentifier(" << pi.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const ProcedureStatement &ps)
{
    return os << "ProcedureStatement(" << ps.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const AssignmentStatement &as)
{
    return os << "AssignmentStatement(target : " << as.target << ", value : " << as.value << ")";
}

std::ostream &operator<<(std::ostream &os, const SimpleStatement &ss)
{
    switch (ss.index())
    {
    case 0:
        return os << "Statement::AssignmentStatement(" << *boost::variant2::get_if<AssignmentStatement>(&ss) << ")";
    case 1:
        return os << "Statement::ProcedureStatement(" << *boost::variant2::get_if<ProcedureStatement>(&ss) << ")";
    case 2:
        return os << "Statement::ReadStatement(" << *boost::variant2::get_if<ReadStatement>(&ss) << ")";
    case 3:
        return os << "Statement::WriteStatement(" << *boost::variant2::get_if<WriteStatement>(&ss) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const StatementPart &sp)
{
    return os << "StatementPart(" << sp.statement << ")";
}

std::ostream &operator<<(std::ostream &os, const Block &b)
{
    return os << "Block(variable_declaration_part : " << b.variable_declaration_part
              << ", procedure_declaration_part : " << b.procedure_declaration_part
              << ", statement_part : " << b.statement_part << ")";
}

std::ostream &operator<<(std::ostream &os, const ProcedureDeclaration &pd)
{
    return os << "ProcedureDeclaration(name : " << pd.name << ", body : " << *pd.body << ")";
}

std::ostream &operator<<(std::ostream &os, const ProcedureDeclarationPart &pdp)
{
    os << "ProcedureDeclarationPart([ ";
    for (int i = 0; i < pdp.procedures.size(); ++i)
    {
        os << pdp.procedures[i];
        if (i < pdp.procedures.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const TypeIdentifier &ti)
{
    return os << "TypeIdentifier(" << ti.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const SimpleType &st)
{
    return os << "SimpleType(" << st.identifier << ")";
}

std::ostream &operator<<(std::ostream &os, const IndexRange &ir)
{
    return os << "IndexRange(begin : " << ir.begin << ", end : " << ir.end << ")";
}

std::ostream &operator<<(std::ostream &os, const ArrayType &at)
{
    return os << "ArrayType(index_range : " << at.index_range << ", element_type : " << at.element_type << ")";
}

std::ostream &operator<<(std::ostream &os, const Type &t)
{
    switch (t.index())
    {
    case 0:
        return os << "Type::SimpleType(" << *boost::variant2::get_if<SimpleType>(&t) << ")";
    case 1:
        return os << "Type::ArrayType(" << *boost::variant2::get_if<ArrayType>(&t) << ")";
    default:
        // unreachable
        return os;
    }
}

std::ostream &operator<<(std::ostream &os, const VariableDeclaration &vd)
{
    os << "VariableDeclaration(identifiers : [ ";
    for (int i = 0; i < vd.identifiers.size(); ++i)
    {
        os << vd.identifiers[i];
        if (i < vd.identifiers.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "], type : " << vd.type << ")";
}

std::ostream &operator<<(std::ostream &os, const VariableDeclarationPart &vdp)
{
    os << "VariableDeclarationPart([ ";
    for (int i = 0; i < vdp.variable_declarations.size(); ++i)
    {
        os << vdp.variable_declarations[i];
        if (i < vdp.variable_declarations.size() - 1)
        {
            os << ",";
        }
        os << " ";
    }
    return os << "])";
}

std::ostream &operator<<(std::ostream &os, const Program &p)
{
    return os << "Program(name : " << p.name << ", body : " << p.body << ")";
}
