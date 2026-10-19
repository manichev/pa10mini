%{
	#include <iostream>
	#include "scanner.h"
	#include "parser.hpp"
	using namespace std;

	typedef grammar::Parser::token token;

	#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%option c++
%option noyywrap
%option batch
%option yylineno
%option debug
%option yyclass = "Scanner"

digit		[0-9]
letter		[a-zA-Z]

integer		{digit}+
exponent	[eE][+-]?{integer}
numeric		[+-]?{integer}("."{integer})?{exponent}?
var			{letter}({digit}*{letter}*)*

%%
%{
    yylloc->step();
%}

[ \t\r]+	{
				yylloc->step();
			}

\n			{
				yylloc->lines(yyleng);
				yylloc->step();
				return token::NEWLINE;
			}

sin			return token::SIN;
				
cos			return token::COS;
				
ln			return token::LN;	
				
,			return token::COMMA;

\+			return token::PLUS;

-			return token::MINUS;

\*			return token::MUL;

\/			return token::DIV;

'			return token::DSIGN;

\^			return token::POW;

\(			return token::LB;

\)			return token::RB;

==			return token::DEQ;

=			return token::EQ;

:=			return token::ASSIGN;

{numeric}	{
				yylval->sval = new string(yytext);
				return token::NUM;
			}
{var}		{
				yylval->sval = new string(yytext);
				return token::VAR;
			}
.			{
				cout<<"Unrecognized symbol"<<"\n";
			}
%% /*** Additional Code ***/

namespace grammar {

Scanner::Scanner(std::istream* in) : yyFlexLexer(in)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}