/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */
/* "%code top" blocks.  */


    #define YYLEX_PARAM &yylval, &yylloc
    #include "scanner.h"
    #include "textdriver.h"






/* First part of user declarations.  */




#include "parser.hpp"

/* User implementation prologue.  */


    #undef yylex
    #define yylex driver.lexer->lex




# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)    \
do {                            \
  if (yydebug_)                        \
    {                            \
      *yycdebug_ << Title << ' ';            \
      yy_symbol_print_ ((Type), (Value), (Location));    \
      *yycdebug_ << std::endl;                \
    }                            \
} while (false)

# define YY_REDUCE_PRINT(Rule)        \
do {                    \
  if (yydebug_)                \
    yy_reduce_print_ (Rule);        \
} while (false)

# define YY_STACK_PRINT()        \
do {                    \
  if (yydebug_)                \
    yystack_print_ ();            \
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok        (yyerrstatus_ = 0)
#define yyclearin    (yychar = yyempty_)

#define YYACCEPT    goto yyacceptlab
#define YYABORT        goto yyabortlab
#define YYERROR        goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace grammar {


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (TextDriver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {
  }

  Parser::~Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  Parser::yy_symbol_value_print_ (int yytype,
               const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
      break;
      }
  }


  void
  Parser::yy_symbol_print_ (int yytype,
               const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
           << ' ' << yytname_[yytype] << " ("
           << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  Parser::yydestruct_ (const char* yymsg,
               int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
    default:
      break;
      }
  }

  void
  Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


/* User initialization code.  */

{
    // initialize the initial location object
    yylloc.begin.filename = yylloc.end.filename = &driver.streamname;
}


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
    yychar = yytoken = yyeof_;
    YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
    yytoken = yytranslate_ (yychar);
    YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
    if (yy_table_value_is_error_ (yyn))
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
    {
    case 8:
    {
            std::cout<<"Initial\n" ;
            std::string val = *(yysemantic_stack_[(3) - (1)].sval);
            driver.daeSystem->setInitial(val,
                atof((yysemantic_stack_[(3) - (3)].sval)->c_str()));
    }
    break;

    case 11:
    {
        std::cout<<"Const\n" ;
        driver.daeSystem->addConstant(*(yysemantic_stack_[(3) - (1)].sval), atof((yysemantic_stack_[(3) - (3)].sval)->c_str()));
    }
    break;

  case 16:

    {
                std::cout<<"Equal\n";
                    driver.daeSystem->addEqual(new Expression(_minus, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree)));
                }
    break;

  case 17:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 18:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 19:

    {
                    (yyval.mtree) = new Expression(_plus, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree));
                }
    break;

  case 20:

    {
                    (yyval.mtree) = new Expression(_minus, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree));
                }
    break;

  case 21:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 22:

    {
                    (yyval.mtree) = new Expression(_multiplication, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree));
                }
    break;

  case 23:

    {
                    (yyval.mtree) = new Expression(_division, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree));
                }
    break;

  case 24:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 25:

    {
                    Expression* tmp = new Expression(-1.0);
                    (yyval.mtree) = new Expression(_multiplication, tmp, (yysemantic_stack_[(2) - (2)].mtree));
                }
    break;

  case 26:

    {
                    (yyval.mtree) = (yysemantic_stack_[(2) - (2)].mtree);
                }
    break;

  case 27:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 28:

    {
                    (yyval.mtree) = new Expression(_power, (yysemantic_stack_[(3) - (1)].mtree), (yysemantic_stack_[(3) - (3)].mtree));
                }
    break;

  case 29:

    {
                    (yyval.mtree) = new Expression(atof((yysemantic_stack_[(1) - (1)].sval)->c_str()));
                    delete (yysemantic_stack_[(1) - (1)].sval);
                }
    break;

  case 30:

    {
                    (yyval.mtree) = (yysemantic_stack_[(3) - (2)].mtree);
                }
    break;

  case 31:

    {
                    (yyval.mtree) = (yysemantic_stack_[(1) - (1)].mtree);
                }
    break;

  case 32:

    {
                    double value;
                    if(driver.daeSystem->constantExists(*(yysemantic_stack_[(1) - (1)].sval), value))
                    {
                        (yyval.mtree) = new Expression(value);
                    }
                    else
                    {
                        std::string val = *(yysemantic_stack_[(1) - (1)].sval);
                        int id = driver.daeSystem->addVariable(val, false);
                        (yyval.mtree) = new Expression(id);
                    }
                }
    break;

  case 33:

    {
                    std::string val = *(yysemantic_stack_[(2) - (1)].sval);
                    int id = driver.daeSystem->addVariable(val, true);
                    (yyval.mtree) = new Expression(-id); //negate for derivative variable
                }
    break;

  case 34:

    {
                    (yyval.mtree) = new Expression(_sin, (yysemantic_stack_[(4) - (3)].mtree));
                }
    break;

  case 35:

    {
                    (yyval.mtree) = new Expression(_cos, (yysemantic_stack_[(4) - (3)].mtree));
                }
    break;

  case 36:

    {
                    (yyval.mtree) = new Expression(_ln, (yysemantic_stack_[(4) - (3)].mtree));
                }
    break;



      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
    && yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
    ++yynerrs_;
    if (yychar == yyempty_)
      yytoken = yyempty_;
    error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;    /* Each real token shifted decrements this.  */

    for (;;)
      {
    yyn = yypact_[yystate];
    if (!yy_pact_value_is_default_ (yyn))
    {
      yyn += yyterror_;
      if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
        {
          yyn = yytable_[yyn];
          if (0 < yyn)
        break;
        }
    }

    /* Pop the current state because it cannot handle the error token.  */
    if (yystate_stack_.height () == 1)
      YYABORT;

    yyerror_range[1] = yylocation_stack_[0];
    yydestruct_ ("Error: popping",
             yystos_[yystate],
             &yysemantic_stack_[0], &yylocation_stack_[0]);
    yypop_ ();
    yystate = yystate_stack_[0];
    YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
             &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char Parser::yypact_ninf_ = -34;
  const signed char
  Parser::yypact_[] =
  {
        16,     2,   -34,    29,    47,    47,    -9,     3,    30,     8,
      16,     4,    42,    35,    44,    -2,    -1,   -34,    39,   -34,
     -34,   -34,    51,    54,    52,    39,    39,    29,    29,    29,
     -34,    56,    42,   -34,     0,    65,    35,    35,   -34,   -34,
      29,    29,    29,    29,    29,    47,   -34,   -34,    57,    58,
      59,   -34,    65,    68,    64,    35,   -34,   -34,   -34,    -1,
      -1,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  Parser::yydefact_[] =
  {
         0,    32,    29,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,    14,     0,    17,    18,    21,    24,    27,
      31,    33,     0,    32,     0,    26,    25,     0,     0,     0,
       1,     0,     4,    10,    32,     3,    14,    14,    15,    13,
       0,     0,     0,     0,     0,     0,    11,    30,     0,     0,
       0,     9,     5,     0,     0,    14,     7,    12,    16,    19,
      20,    22,    23,    28,    34,    35,    36,     8,     6
  };

  /* YYPGOTO[NTERM-NUM].  */
  const signed char
  Parser::yypgoto_[] =
  {
       -34,   -34,    43,   -29,   -34,    66,    67,   -33,   -11,    -3,
     -34,   -24,   -15,    34,    33,   -34
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  Parser::yydefgoto_[] =
  {
        -1,     9,    35,    36,    10,    11,    12,    39,    13,    14,
      15,    16,    17,    18,    19,    20
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char Parser::yytable_ninf_ = -1;
  const unsigned char
  Parser::yytable_[] =
  {
        24,    37,    27,    56,    57,    21,    55,    21,    30,    53,
      22,    33,    41,    42,    28,    43,    44,    59,    60,     1,
       2,    37,    68,    55,    48,    49,    50,     3,    61,    62,
       4,     5,    23,     2,     6,     7,     8,    58,    25,    26,
       3,    29,    38,     4,     5,    34,     2,     6,     7,     8,
      23,     2,    45,     3,    40,    46,     4,     5,     3,    21,
       6,     7,     8,    51,    47,     6,     7,     8,    54,    64,
      65,    66,    67,    53,     0,    52,    31,    32,    63
  };

  /* YYCHECK.  */
  const signed char
  Parser::yycheck_[] =
  {
         3,    12,    11,    36,    37,     5,    35,     5,     0,     9,
       8,     7,    14,    15,    11,    16,    17,    41,    42,     3,
       4,    32,    55,    52,    27,    28,    29,    11,    43,    44,
      14,    15,     3,     4,    18,    19,    20,    40,     4,     5,
      11,    11,     7,    14,    15,     3,     4,    18,    19,    20,
       3,     4,    13,    11,    10,     4,    14,    15,    11,     5,
      18,    19,    20,     7,    12,    18,    19,    20,     3,    12,
      12,    12,     4,     9,    -1,    32,    10,    10,    45
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  Parser::yystos_[] =
  {
         0,     3,     4,    11,    14,    15,    18,    19,    20,    22,
      25,    26,    27,    29,    30,    31,    32,    33,    34,    35,
      36,     5,     8,     3,    30,    34,    34,    11,    11,    11,
       0,    26,    27,     7,     3,    23,    24,    29,     7,    28,
      10,    14,    15,    16,    17,    13,     4,    12,    30,    30,
      30,     7,    23,     9,     3,    24,    28,    28,    30,    32,
      32,    33,    33,    35,    12,    12,    12,     4,    28
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  Parser::yyr1_[] =
  {
         0,    21,    22,    22,    22,    22,    23,    23,    24,    25,
      25,    26,    27,    27,    28,    28,    29,    30,    31,    31,
      31,    32,    32,    32,    33,    33,    33,    34,    34,    35,
      35,    35,    35,    35,    36,    36,    36
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  Parser::yyr2_[] =
  {
         0,     2,     1,     2,     2,     3,     3,     2,     3,     3,
       2,     3,     3,     2,     0,     1,     3,     1,     1,     3,
       3,     1,     3,     3,     1,     2,     2,     1,     3,     1,
       3,     1,     1,     2,     4,     4,     4
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const Parser::yytname_[] =
  {
    "$end", "error", "$undefined", "VAR", "NUM", "DSIGN", "COMMA",
  "NEWLINE", "ASSIGN", "DEQ", "EQ", "LB", "RB", "POW", "PLUS", "MINUS",
  "MUL", "DIV", "SIN", "COS", "LN", "$accept", "document", "initial_list",
  "initial", "const_list", "const", "system", "termsymbol", "equal",
  "expr", "addexpr", "mulexpr", "unaryexpr", "powexpr", "atomexpr", "func", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const Parser::rhs_number_type
  Parser::yyrhs_[] =
  {
        22,     0,    -1,    27,    -1,    27,    23,    -1,    25,    27,
      -1,    25,    27,    23,    -1,    23,    24,    28,    -1,    24,
      28,    -1,     3,     9,     4,    -1,    25,    26,     7,    -1,
      26,     7,    -1,     3,     8,     4,    -1,    27,    29,    28,
      -1,    29,    28,    -1,    -1,     7,    -1,    30,    10,    30,
      -1,    31,    -1,    32,    -1,    31,    14,    32,    -1,    31,
      15,    32,    -1,    33,    -1,    32,    16,    33,    -1,    32,
      17,    33,    -1,    34,    -1,    15,    34,    -1,    14,    34,
      -1,    35,    -1,    34,    13,    35,    -1,     4,    -1,    11,
      30,    12,    -1,    36,    -1,     3,    -1,     3,     5,    -1,
      18,    11,    30,    12,    -1,    19,    11,    30,    12,    -1,
      20,    11,    30,    12,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned char
  Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     8,    11,    15,    19,    22,    26,
      30,    33,    37,    41,    44,    45,    47,    51,    53,    55,
      59,    63,    65,    69,    73,    75,    78,    81,    83,    87,
      89,    93,    95,    97,   100,   105,   110
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned char
  Parser::yyrline_[] =
  {
         0,    75,    75,    76,    77,    78,    81,    82,    84,    91,
      92,    94,   100,   101,   103,   104,   106,   112,   117,   121,
     125,   130,   134,   138,   143,   147,   152,   157,   161,   166,
     171,   175,   179,   192,   198,   202,   206
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
     i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
           << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
               yyrhs_[yyprhs_[yyrule] + yyi],
               &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
               &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int Parser::yyeof_ = 0;
  const int Parser::yylast_ = 78;
  const int Parser::yynnts_ = 16;
  const int Parser::yyempty_ = -2;
  const int Parser::yyfinal_ = 30;
  const int Parser::yyterror_ = 1;
  const int Parser::yyerrcode_ = 256;
  const int Parser::yyntokens_ = 21;

  const unsigned int Parser::yyuser_token_number_max_ = 275;
  const Parser::token_number_type Parser::yyundef_token_ = 2;


} // grammar



void grammar::Parser::error( const grammar::Parser::location_type &l, const std::string &err_message )
{
    driver.error(l, err_message);
}
