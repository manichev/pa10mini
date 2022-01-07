#pragma once

#include <string>
#include <QString>

#include "daesystem.h"
#include "position.hh"
#include "location.hh"
#include "parser.hpp"
#include "scanner.h"
#include "pax_prototype.h"

class TextDriverException
{
public:
    TextDriverException(QString message_){ message = message_; };
    ~TextDriverException(){};
	QString reason() {return message; };
private:
	QString message;
};

namespace grammar{

class TextDriver
{
friend Parser;
public:
	TextDriver(DAESystem* sys);

    bool parse_stream(std::istream& in, const std::string& sname = "stream input");
    bool parse_string(const std::string& input, const std::string& sname = "string stream");
    bool parse_file(const std::string& filename);
	void error(const grammar::Parser::location_type &l, const std::string &err_message);

private:
	Scanner* lexer;
	Parser* daeparser;
	DAESystem* daeSystem;

	bool trace_scanning;
	bool trace_parsing;
	std::string streamname;
	PAX_Prototype *parent;
};

}