#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

extern int symb;
extern char * yytext;

char * showSymb(int symb)
{ switch(symb)
{ case METHOD: return "method";
case BEG: return "begin";
case ENDMETHOD: return "endmethod";
case VARS: return "vars";
case ASSIGN: return ":=";
case IF: return "if";
case THEN: return "then";
case ELSE: return "else";
case ENDIF: return "endif";
case WHILE: return "while";
case ENDWHILE: return "endwhile";
case LBR: return "(";
case RBR: return ")";
case READ: return "read";
case WRITE: return "write";
case LESS: return "less";
case LESSEQ: return "lessEq";
case EQ: return "eq";
case NEQ: return "nEq";
case SEMI: return ";";
case COMMA: return ",";
case PLUS: return "plus";
case TIMES: return "times";
case MINUS: return "minus";
case DIVIDE: return "divide";
case ID: return "ID";
case INT: return "INT";
case RETURN: return "return";
case EOF: return "EOF";
default: printf("bad symbol: %d",symb);
    }
}

printSymb()
{ char * s;
printf("%s ",showSymb(symb));
if(symb==ID || symb==INT){
if(yytext == NULL)
printf("Error: yytext is null");
else
printf("%s\n",yytext);
} else
printf("\n");}
