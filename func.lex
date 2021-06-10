/*
 *This is where you specify the rules for your FUNC lexical analyser. Once you have completed
 * it, you will need to use FLEX to generate a lexical analyser from this file.
 */
 
%{
#include "tokens.h"
%}

/*  ^0|[0-9]*[1-9]+$|^[1-9]+[0-9]*$   */
INT [1-9]
ID [a-zA-Z][A-Za-z0-9]*


%%
"method"        { return METHOD;}
"begin"        { return BEG;}
"endmethod"     { return ENDMETHOD;}
"vars"        { return VARS;}
":="        { return ASSIGN;}
"if"        { return IF;}
"then"        { return THEN;}
"else"        { return ELSE;}
"endif"        { return ENDIF;}
"while"        { return WHILE;}
"endwhile"        { return ENDWHILE;}
"("        { return LBR;}
")"        { return RBR;}
"read"        { return READ;}
"write"        { return WRITE;}
"less"        { return LESS;}
"lessEq"        { return LESSEQ;}
"eq"        { return EQ;}
"nEq"        { return NEQ;}
";"        { return SEMI;}
","        { return COMMA;}
"return"     { return RETURN;}

{ID}	 {return ID;}
(0|{INT}*{INT}+)|({INT}+[0-9]*)  {return INT;}
<<EOF>>	 { return EOF; }

[ \t\n]+ /* eat up whitespace */



%%

int yywrap() { return EOF; }