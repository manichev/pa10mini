#include "textdriver.h"


#include <fstream>
#include <sstream>

#include <QString>
#include <QLabel>

namespace grammar
{

TextDriver::TextDriver(DAESystem* sys): trace_scanning(false), trace_parsing(false)
{
    daeSystem = sys;
}


bool TextDriver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner daescanner(&in);
    daescanner.set_debug(trace_scanning);
    this->lexer = &daescanner;

    daeparser = new Parser (*this);
    daeparser->set_debug_level(trace_parsing);
    return (daeparser->parse() == 0);
}


bool TextDriver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}


bool TextDriver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void TextDriver::error(const grammar::Parser::location_type &loc, const std::string &err_message)
{
    QString message = QString::fromStdString(err_message);
    message.prepend("Error: ");

    message.replace("VAR", "variable");
    message.replace("NUM", "number");
    message.replace("DSIGN", "\"'\"");
    message.replace("COMMA", "\",\"");
    message.replace("NEWLINE", "newline");
    message.replace("ASSIGN", ":=");
    message.replace("DEQ", "\"==\"");
    message.replace("EQ", "\"=\"");
    message.replace("LB", "\"(\"");
    message.replace("RB", "\")\"");
    message.replace("POW", "\"^\"");
    message.replace("PLUS", "\"+\"");
    message.replace("MINUS", "\"-\"");
    message.replace("MUL", "\"*\"");
    message.replace("DIV", "\"/\"");
    message.replace("SIN", "\"sin\"");
    message.replace("COS", "\"cos\"");
    message.replace("LN", "\"ln\"");
    message.replace("$end", "end");

    message.append(" at line");
    message.append(QString::number(loc.begin.line));
    message.append(".");
    throw TextDriverException(message);
}

}
