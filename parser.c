/**
 * Solutions to Q2: Implement your Recursive Decent Parser here.
 * Note here you do not need to produce an AST as output.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

//////////////////////////////////////////////////


// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

//////////////////////////////////////////////////

// 
//----------------HELPER FUNCTIONS------------//
/**
 * Similar to showSymb() from the lecture notes. 
 */
char * getSymb(int s)
{  switch(s)
   {  
      case METHOD: return "method";
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
      case ID: return "ID";
      case INT: return "INT";
      case RETURN: return "return";
      case EOF: return "EOF";
      default: 
         printf("bad symbol: %d",s);
         return NULL;
   }
}

void error(char * rule, char * message)
{  printf("%s: found %s\n",rule,getSymb(symb));
   printf("%s: %s\n",rule,message);
   exit(0);
}

lex()
{ 
   printSymb();
   symb = yylex();
}

printSymb()
{
   char *s;
   printf("%s ", getSymb(symb));
   if (symb == ID || symb == INT)
   {
      if (yytext == NULL)
         printf("Error: yytext is null");
      else
         printf("%s\n", yytext);
   }
   else
      printf("\n");
}

/* rule(char * name,int depth)
{ 
   int i;
   for(i=0;i<depth;i++)
   printf(" ");
   printf("%s\n",name);
}  */


//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 */ 
void program(int depth)
{
	/*
	 * YOUR CODE HERE
    * Remove the following line of code when done.
	 */
   rule("program", depth);
   methods(depth+1);
}

/**
 * 
 * YOUR CODE HERE
 * Add methods corresponding to the Non-terminals in the FUNC grammar below here
 * 
 */


//<methods> ::= <method>;[<methods>]
methods(int depth)   {
   rule("methods", depth);
   method(depth+1);
   if(symb!=SEMI) {
      error("methods","; expected\n");
   }
   lex();
   if(symb==METHOD)
   {
      methods(depth);
   }
}

//<method> ::= method <id>([<args>]) [vars <args>] begin <statements> [return <id>;] endmethod
method(int depth) {
   rule("method", depth);
   if(symb!=METHOD)  {
      error("method", "method expected\n");
   }
   lex();
   if(symb!=ID)   {
      error("method", "id expected\n");  
   }
   id(depth+1);

   if(symb!=LBR)  { 
      error("method", "( expected\n");
   }
   lex();

   if(symb==ID)   {
      args(depth+1);
   }

   if(symb!=RBR)  {
      error("method", ") expected\n");
   }
   lex();

   if(symb==VARS) {
      lex();
      args(depth+1);
   }

   if(symb!=BEG)  {
      error("method","begin expected\n");
   }
   lex();

   statements(depth+1);

   if(symb==RETURN)  {
      lex();
      id(depth+1);
      if(symb!=SEMI) {
         error("return","; expected\n");   
      }
      lex();
   }

   if(symb!=ENDMETHOD)  {
      error("method", "endmethod expected\n"); 
   }
   lex();
}
   
//<args> ::= <id>[,<args>]
args(int depth)   {
   rule("args", depth);
   id(depth+1);
   if(symb==COMMA) {
      lex();
      args(depth+1);
   }
}

//<statements> ::= <statement>;[<statements>]
statements(int depth)   {
   rule("statements", depth);
   statement(depth+1);
   if(symb!=SEMI) {
      error("statements","; expected\n");
   }
   lex();
   if(symb==READ || symb==WRITE || symb == ID || symb == IF || symb == WHILE) {
      statements(depth+1);
   }
}


//<statement> ::= <assign> | <if> | <while> | <rw>
statement(int depth) {
   rule("statement", depth);
   switch(symb)
   {
      case ID:
         assign(depth+1);
         break;
      case IF:
         iff(depth+1);
         break;
      case WHILE:
         whiles(depth+1);
         break;
      case READ:
         rw(depth+1);
         break;
      case WRITE:
         rw(depth+1);
         break;
      default:
      error("statement", "read/write/id/if/while expected\n");
   }
}

//<rw> ::= read <id> | write <exp>
rw(int depth)  {
   rule("rw", depth);
   switch(symb)   {
      case READ: lex();
      id(depth+1);
      break;
      case WRITE: lex();
      exp(depth+1);
      break;
      default:
      error("rw","read/write expected\n");
   }

/*   if(symb!=READ) {
      error("read", "read expected\n");
   }
   else  {
      lex();
      id(depth+1);
   }

   if(symb!=WRITE)   {
      error("write", "write expected\n");
   }
   else  {
      lex();
      exp(depth+1);
   }  */
}

//<assign> ::= <id> := <exp>
assign (int depth)   {
   rule("assign",depth);
   id(depth+1);
   if(symb!=ASSIGN)  {
      error("assign",":= expected\n"); 
   }
   lex();
   exp(depth+1);
}

//<if> ::= if <cond> then <statements> [else <statements>] endif
iff(int depth)
{
   rule("if", depth);
   if(symb!=IF)   {
      error("if", "if expected\n");
   }
   lex();

   cond(depth + 1);

   if (symb != THEN)
   {
      error("if", "then expected\n");
   }
   lex();

   statements(depth + 1);

   if (symb == ELSE)
   {
      lex();
      statements(depth + 1);
   }

   if (symb != ENDIF)
   {
      error("if", "endif expected\n");
   }
   lex();
}

/*whiles(int depth)
{
   rule("while", depth);
   cond(depth + 1);
   if (symb == BEG)  {
      lex();
   }
   //lex();
   statements(depth + 1);
   if(symb != ENDWHILE)   {
      error("while", "endwhile expected\n");
   }
   lex();
}*/

//<while> ::= while <cond> begin <statements> endwhile
whiles(int depth)
{ 
   rule("while",depth);
   if(symb!=WHILE)   {
      error("while", "while expected\n");
   }
   lex();

   cond(depth+1);

   if(symb!=BEG)  {
      error("while", "begin expected\n");
   }
   lex();

   statements(depth+1);

   if(symb != ENDWHILE)   {
      error("while", "endwhile expected\n");
   }
   lex();
}




//<cond> ::= <bop> ( <exps> )
cond(int depth)
{
   rule("cond", depth);
   bop(depth + 1);
   if (symb != LBR)  {
      error("cond", "( expected\n");
   }
   lex();
   
   exps(depth + 1);

   if (symb != RBR)  {
      error("cond",") expected\n");      
   }
   lex();
}

//<bop> ::= less | lessEq | eq | nEq
bop(int depth)
{
   rule("bop", depth);
   switch (symb)
   {
   case LESS:
   case LESSEQ:
   case EQ:
   case NEQ:
      lex();
      return;
   default:
      error("bop", "less/lesseq/eq/neq expected\n");
   }
}


//<exps> ::= <exp> [,<exps>]
exps(int depth)
{
   rule("exps", depth);
   exp(depth + 1);
   if (symb == COMMA)   {
      lex();
      exps(depth+1);
   }
}

//<exp> ::= <id>[( <exps> )] | <int>
exp(int depth)
{
   rule("exp", depth);
   switch(symb)   {
      case ID: id(depth+1);
      if(symb==LBR)  {
         lex();
         exps(depth+1);
         if(symb!=RBR)  {
            error("exp",") expected\n");
         }
         lex();
      }
      break;
      case INT: integer(depth+1);
      break;
      default:
      error("exp","id/int expected\n");
   }
 /*  if(symb!=ID)   {
      error("exp","id expected\n");
   }
   else  {
      id(depth+1);
      if(symb==LBR)  {
         lex();
         exps(depth+1);
         if(symb!=RBR)  {
            error("exp",") expected\n");
         }
         lex();
      }
   }

   if(symb!=INT)  {
      error("exp","int expected\n");
   }
   lex();   */

 /*  switch (symb)
   {
   case ID:
      lex();
      if(symb==LBR)  {
         lex();
         exps(depth+1);
         if(symb==RBR)  {  
            lex();   
         }
      }
         if (symb == LBR)  {
            lex();
            exps(depth+1);

            if (symb == ID)   {
               lex();
            }

         if (symb != RBR)  {
            error("exp",") expected\n");
         }
         lex();
      }
      break;
   case INT: break;
   case RBR:
      break;
   default:
      error("exp", "id or int expected\n");
   }
   lex();   */
}

/*   lex();
   if(symb==LBR)  {
      lex();
      exps(depth+1);
      if(symb!=RBR)  {
         error("exps", ") expected\n");
      }
      else  {lex();}
   }
}*/

integer(int depth)   {
   rule("int",depth);
   lex();
}

id(int depth)   {
   rule("id",depth);
   lex();
}
//////////////////////////////////////////////////



/**
 * Execution starts here
 */
int main(int argc, char **argv)
{
	// open the file to be parsed, if possible
	if ((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("can't open %s\n", argv[1]);
		exit(0);
	}
   symb = yylex();
	program(1);
	fclose(yyin);
}