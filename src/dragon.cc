/*
 * dragon.cc
 * Copyright (C) 2016 sabertazimi <sabertazimi@avalon>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "syntax/Tree.h"
#include "semantic/Scope.h"
#include "semantic/semantic.h"
#include "syntax/AstPrinter.h"

#define AST_DEBUG
#undef AST_DEBUG

#define SEMA_DEBUG
// #undef SEMA_DEBUG

extern FILE *yyin;
extern int yyparse(void);
extern Program *tree;
extern int parse_failed;

ScopeStack *gtable;

int main(int argc, char **argv) {
    FILE *fp = NULL;

    if (argc > 1 && (fp = fopen(argv[1], "r")) != NULL) {
        yyin = fp;
    }

    // yyparse return value: 1 represent error occurs
    while (yyparse()) {
        fprintf(stderr, "*** bison panic!\n");
        exit(1);
    }

    if (parse_failed == 1) {
        fprintf(stderr, "*** please fix syntax error first!\n");
        exit(0);
    }

#ifdef AST_DEBUG
    AstPrinter *ap = new AstPrinter();
    tree->print(ap);
#endif

    // set up global scope stack
    gtable = new ScopeStack();

	BuildSymbol *bs = new BuildSymbol(gtable);
    bs->visitProgram(tree);
	TypeCheck *tc = new TypeCheck(gtable);
    tc->visitProgram(tree);

    if (bs->failed == 1 || tc->failed == 1) {
        fprintf(stderr, "*** please fix semantic error first!\n");
        // exit(0);
    }

#ifdef SEMA_DEBUG
    AstPrinter *ap = new AstPrinter();
    tree->globalScope->print(ap);
#endif

    fclose(fp);
    return 0;
}
