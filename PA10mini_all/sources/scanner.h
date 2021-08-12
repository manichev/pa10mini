#pragma once
 
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#undef  YY_DECL
#define	YY_DECL									\
    int	grammar::Scanner::lex(					\
	grammar::Parser::semantic_type* yylval,		\
	grammar::Parser::location_type* yylloc		\
    )

#include "parser.hpp"

namespace grammar
{

class Scanner : public yyFlexLexer
{
public:
	Scanner(std::istream *in);
	~Scanner();
	void set_debug(bool b);

    virtual int lex(Parser::semantic_type* yylval, Parser::location_type* yylloc);
};

} /* end namespace grammar */
