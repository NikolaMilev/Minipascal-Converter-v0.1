%option noyywrap
%option nounput
%option caseless
%{

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "expression.hpp"
#include "statement.hpp"
#include "parser.tab.hpp"

%}

%%
\{[^}]*\} {/*a comment*/}
begin {return BEGIN_TOKEN;}
end {return END_TOKEN;}
while { return WHILE_TOKEN; }
do { return DO_TOKEN; }
if { return IF_TOKEN; }
then { return THEN_TOKEN; }
else { return ELSE_TOKEN; }
for { return FOR_TOKEN;}
to { return TO_TOKEN; }
div { return DIV_TOKEN; }
mod { return MOD_TOKEN; }
or { return OR_TOKEN; }
and { return AND_TOKEN; }
downto { return DOWNTO_TOKEN; }
repeat { return REPEAT_TOKEN; }
until { return UNTIL_TOKEN; }
writeln|write { return OUTPUT_TOKEN; }
readln|read { return INPUT_TOKEN; }
[A-Za-z_][A-Za-z0-9]* { yylval.s = new string(yytext); return IDENTIFIER;}
[0-9]+|[0-9]*\.[0-9]+|[0-9]+e(-?)[0-9]+ {yylval.v = new string(yytext); return CONST_TOKEN;}
:= {return ASSIGN_TOKEN;}
"<>" { return NOTEQUAL_TOKEN; }
"<=" { return LE_TOKEN; }
">=" { return GE_TOKEN; }
[+\-*/<>;()=.,] return *yytext;
"]"|"[" return *yytext;
\'[^\n']*\' { yylval.str = new string(yytext); return STRING_TOKEN;}
[ \t\n]+ {}
. { cerr << "ERROR: Unrecognized input character." << *yytext << endl; exit(EXIT_FAILURE); }

%%
