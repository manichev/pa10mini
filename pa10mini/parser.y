/*** C/C++ declarations ***/

%code top
{
	#define YYLEX_PARAM &yylval, &yylloc
	#include "scanner.h"
	#include "textdriver.h"

}

%code requires
{
	namespace grammar
	{
		class Scanner;
		class TextDriver;
	}
	#include "expression.h"
}

%union
{
	std::string* sval;
	Expression* mtree;
}


/*** bison declarations ***/
/* location traking */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};
/*  use newer C++ skeleton file*/
%skeleton "lalr1.cc"

/* require bison 2.5 or later */
%require  "2.5"

/*add debug output code to generated parser. disable this for release versions.*/
%debug

/* verbose error messages */
%error-verbose

/* write out a header file containing the token defines */
%defines

/* define parser namespace */
%define namespace "grammar"

/* set the parser's class identifier */
%define parser_class_name "Parser"

%parse-param	{ TextDriver& driver }
/* keep track of the current position within the input */

%token	<sval>	VAR NUM DSIGN COMMA NEWLINE
%token	<sval>	ASSIGN DEQ EQ LB RB POW PLUS MINUS MUL DIV 
%token	<sval>	SIN COS LN
%type	<sval>	termsymbol
%type	<mtree>	atomexpr powexpr unaryexpr mulexpr addexpr expr func
%type	<mtree>	equal system initial initial_list document   const const_list

/*%destructor { delete $$; } atomexpr powexpr unaryexpr mulexpr addexpr expr equal system*/

%{
	#undef yylex
	#define yylex driver.lexer->lex
%}

%%
document		:	system
				|	system initial_list
				|	const_list system
				|	const_list system initial_list;
				

initial_list	:	initial_list initial termsymbol;
				|	initial termsymbol;
				
initial			:	VAR DEQ	NUM 
				{
					std::cout<<"Initial\n" ;
					driver.daeSystem->setInitial(string(*$<sval>1),
						atof($<sval>3->c_str()));
				};

const_list		:	const_list const NEWLINE
				|	const NEWLINE;

const			:	VAR ASSIGN NUM
				{
				std::cout<<"Const\n" ;
					driver.daeSystem->addConstant(*$<sval>1, atof($<sval>3->c_str()));
				};
								
system			:	system equal termsymbol  
				|	equal termsymbol;
				
termsymbol		: 
				| NEWLINE;

equal			:	expr EQ expr
				{
				std::cout<<"Equal\n";
					driver.daeSystem->addEqual(new Expression(_minus, $1, $3));
				};

expr			:	addexpr
				{
					$$ = $1;
				};

addexpr			:	mulexpr
				{
					$$ = $1;
				}
				|	addexpr	PLUS	mulexpr
				{
					$$ = new Expression(_plus, $1, $3);
				}
				|	addexpr	MINUS	mulexpr
				{
					$$ = new Expression(_minus, $1, $3);
				};

mulexpr			:	unaryexpr
				{
					$$ = $1;
				}
				|	mulexpr	MUL	unaryexpr
				{
					$$ = new Expression(_multiplication, $1, $3);
				}
				|	mulexpr	DIV	unaryexpr
				{
					$$ = new Expression(_division, $1, $3);
				};

unaryexpr		:	powexpr
				{
					$$ = $1;
				}
				|	MINUS powexpr
				{
					Expression* tmp = new Expression(-1.0);
					$$ = new Expression(_multiplication, tmp, $2);
				}
				|	PLUS powexpr
				{
					$$ = $2;
				};

powexpr			:	atomexpr
				{
					$$ = $1;
				}
				|	powexpr	POW	atomexpr
				{
					$$ = new Expression(_power, $1, $3);
				};

atomexpr		:	NUM
				{
					$$ = new Expression(atof($<sval>1->c_str()));
					delete $<sval>1;
				}
				|	LB expr RB
				{
					$$ = $2;
				}
				|	func
				{
					$$ = $1;
				}			
				|	VAR
				{
					double value;
					if(driver.daeSystem->constantExists(*$<sval>1, value))
					{
						$$ = new Expression(value);
					}
					else
					{
						int id = driver.daeSystem->addVariable(string(*$<sval>1), false);
						$$ = new Expression(id);
					}
				}
				|	VAR DSIGN
				{
					int id = driver.daeSystem->addVariable(string(*$<sval>1), true);
					$$ = new Expression(-id); //negate for derivative variable
				};
			
func			:	SIN LB expr RB
				{
					$$ = new Expression(_sin, $3);
				}
				|	COS LB expr RB
				{
					$$ = new Expression(_cos, $3);
				}
				|	LN LB expr RB
				{
					$$ = new Expression(_ln, $3);
				}
%%
void grammar::Parser::error( const grammar::Parser::location_type &l, const std::string &err_message )
{
	driver.error(l, err_message);
}