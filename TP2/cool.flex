/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%option noyywrap
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;

/*
 *  Add Your own definitions here
 */

 int comment_op = 0;

%}

%x STRING COMMENT
/*
 * Define names for regular expressions here.
 */
ASSIGN          <-
DARROW          =>
LE              <=


INTEGER       [0-9]+
TYPE          [A-Z][A-Za-z0-9_]+
OBJECT	      [a-z][a-zA-Z0-9_]+

TRUE          (t)(?i:rue)
FALSE         (f)(?i:alse)

WS            [ \n\f\r\t\v]
SC            "+"|"/"|"-"|"*"|"="|"<"|"."|"~"|","|";"|":"|"("|")"|"@"|"{"|"}"

%%
\n    curr_lineno++;


{INTEGER}	
    {
      cool_yylval.symbol = inttable.add_int(yytext);
      return INT_CONST;
		}

{TYPE}
    {
      cool_yylval.symbol = idtable.add_string(yytext);
      return TYPEID;
    }

{OBJECT}|(self)
    {
      cool_yylval.symbol = idtable.add_string(yytext);
      return OBJECTID;
    }


 /*
  *  Nested comments
  */

  --[.]*


"*)"
      {
        cool.yylval.error_msg = "Unmatched *)"
        return ERROR;
      }

"(*"
    {
      comment_op++;
      BEGIN(COMMENT);
    }

<COMMENT>"(*"
    {
      comment_op++;
    }

<COMMENT>"*)"
    {
      comment_op--;
      if(comment_op==0)
        BEGIN(INITIAL);
    }
<COMMENT><<EOF>>
    {
      cool_yylval.error_msg = "EOF in comment";
      BEGIN(INITIAL);
      comment_op = 0;
      return ERROR;
    }

 /*
  *  The multiple-character operators.
  */
{ASSIGN}    { return (ASSIGN); }
{DARROW}		{ return (DARROW); }
{LE}        { return (LE);}

 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
(?i:class)     { return (CLASS);}
(?i:else)      { return (ELSE);}
(?i:fi)        { return (FI);}
(?i:if)        { return (IF);}
(?i:in)        { return (IN);}
(?i:inherits)  { return (INHERITS);}
(?i:let)       { return (LET);}
(?i:loop)      { return (LOOP);}
(?i:pool)      { return (POOL);}
(?i:then)      { return (THEN);}
(?i:while)     { return (WHILE);}
(?i:case)      { return (CASE);}
(?i:esac)      { return (ESAC);}
(?i:of)        { return (OF);}
(?i:new)       { return (NEW);}
(?i:isvoid)    { return (ISVOID);}
(?i:not)       { return (NOT);}

{TRUE} 
      {
        cool_yylval.boolean = true;
        return BOOL_CONST;
      }

{FALSE} 
        {
          cool_yylval.boolean = false;
          return BOOL_CONST;
        }

{SC}
    {
      return (yytext);
    }


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */
%%
