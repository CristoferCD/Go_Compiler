%{
	#include "definiciones.h"
	#include "gestorErrores.h"
	char* commentStart;
	int currentLine = 1;
	int commentLineStart;
%}

/* Letters and digits */

letter		[_a-zA-Z]
decimal_digit	[0-9]
octal_digit	[0-7]
hex_digit	[0-9A-Fa-f]

/* Identifiers */

identifier	{letter}[_a-zA-Z0-9]*

/* Integer literals */

int_lit		({decimal_lit})|({octal_lit})|({hex_lit})
decimal_lit	[1-9]{decimal_digit}*
octal_lit	0{octal_digit}*
hex_lit		0[xX]?{hex_digit}+

/* Floating-point literals */

float_lit	({decimals}\.{decimals}?{exponent}?)|({decimals}{exponent})|(\.{decimals}{exponent}?)
decimals	{decimal_digit}+
exponent	[eE][+-]?{decimals}

/* Imaginary literals */

imaginary_lit	({decimals}|{float_lit})i

/* Comment rule */

%x	MULTI_COMMENT
%x	SINGLE_COMMENT

%%
{imaginary_lit}			{ return LIT_IMAGINARY; }
{float_lit}			{ return LIT_FLOAT; }
{int_lit}			{ return LIT_INTEGER; }
{identifier}			{ if (strcmp(yytext, "_") == 0) return BLANKID; else return ID; }

<INITIAL>"/*"			{ commentStart = yytext; commentLineStart = currentLine;  BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*"+"/"		{ BEGIN(INITIAL);  if(commentLineStart == currentLine) return ' '; else return LINEBREAK; }
<MULTI_COMMENT>[^*\n]*		// Ignore
<MULTI_COMMENT>"*"+[^*/\n]*	// Ignore
<MULTI_COMMENT>\n		{ currentLine++; }
<MULTI_COMMENT><<EOF>>		{ error_log("[LEX] Error analyzing multiline comment. Not closed\n", commentLineStart); }

<INITIAL>"//"			{ commentStart = yytext; BEGIN(SINGLE_COMMENT); }
<SINGLE_COMMENT>[^\r?\n]+	// Ignore content
<SINGLE_COMMENT>\r?\n		{ BEGIN(INITIAL); return ' '; }

{letter}?\"(\\.|[^\\"])*\"	{ return LIT_STRING; }
[ \r\t]				// Ignore
\n				{ currentLine++; return LINEBREAK; }

"+="				{ return OP_PLUSEQ; }
"&="				{ return OP_AMPEQ; }
"&&"				{ return OP_AMPAMP; }
"=="				{ return OP_EQEQ; }
"!="				{ return OP_NEQ; } 
"-="				{ return OP_SUBEQ; }
"|="				{ return OP_OREQ; }
"||"				{ return OP_OROR; }
"<="				{ return OP_LEQ; }
"*="				{ return OP_MULTEQ; }
"^="				{ return OP_EXPEQ; }
"<-"				{ return OP_LEFTARROW; }
">="				{ return OP_MEQ; }
"<<"				{ return OP_LESSLESS; }
"/="				{ return OP_FORWARDSLASHEQ; }
"<<="				{ return OP_LESSLESSEQ; }
"++"				{ return OP_PLUSPLUS; }
":="				{ return OP_COLONEQ; }
">>"				{ return OP_MOREMORE; }
"%="				{ return OP_PERCENTAGEEQ; }
">>="				{ return OP_MOREMOREEQ; }
"--"				{ return OP_SUBSUB; }
"..."				{ return OP_DOTS; }
"&^"				{ return OP_AMPEXP; }
"&^="				{ return OP_AMPEXPEQ; }
.				{ return *yytext; }
<INITIAL><<EOF>>		{ return EOF; }
%%
