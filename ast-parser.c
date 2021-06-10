/**
 * Solution to Q3: Implement the AST parser here. Note that this
 * is essentially an extension of the solutions to Q2, so you 
 * may wish to copy and paste your solutions and extend that.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "tree.h"

//////////////////////////////////////////////////

// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

//////////////////////////////////////////////////

// HELPER FUNCTIONS
//----------------------------------------------//


/**
 * Similar to showSymb from the lecture notes. 
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
{  printf("%s: found %s\n", rule, getSymb(symb));
   printf("%s: %s\n", rule, message);
   exit(0);
}




//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 *  It corresponds to the top level, start symbol of FUNC grammars.
 */ 
struct node *program()
{
	/* 
	 * YOUR CODE HERE
	 */
	extern newInternalNode* methods();
	node* p;
	p = newInternalNode(METHOD);
	p->addBranch(p, methods);
	return p;
}


/**
 * 
 * YOUR CODE HERE
 * 
 * Add methods corresponding to the non-terminals in the FUNC grammar, and other code below here.
 * 
 */
struct node *methods()	{
	extern newInternalNode* method();
	node * m;
	m = method();
	if(symb == SEMI)	{
		lex();
		if(symb == METHOD)	{
			node * m1;
			m1 = m;
			m = newInternalNode(SEMI);
			d->addBranch(d, m1);
			d->addBranch(d, methods());
		}
	}
	else	{
		error("methods", "; expected\n");
	}
	return m;
}

struct node * method()	{
	node * m;
	if(symb != METHOD)	{
		error("method", "method expected\n");
	}
	lex();
	if(symb!=ID)	{
		error("method", "id expected\n");
	}
	m = newInternalNode(METHOD);
	m->addBranch(m, newId(yytext));

}


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

	struct node *progtree = program();
	if (progtree == NULL)
	{
		printf("program() returned null. Methods unimplemented?\n");
		return -1;
	}
	printTree(progtree);
	fclose(yyin);
}