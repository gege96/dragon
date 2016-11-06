/*
 * sema_symtab.c
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "sema_symtab.h"

int symtab_failed = 0;

static int cnt_offset = 0;

symbol_t symbol_new(symbol_kind_t kind, yyltype loc, const char *id, void *def) {
    symbol_t symbol = (symbol_t)malloc(sizeof(*symbol));
    symbol->kind = kind;
    symbol->id = strdup(id);
    symbol->loc = loc;
    symbol->def = def;
    symbol->offset = cnt_offset++;
}

/*
 * when travel ast tree first time, set up all scope_t in class_def_t or func_def_t
 * 1. create empty scope
 * 2. bind a specific def_t to a symbol_t (set up id -> def_t mapping)
 * 3. add symbol_t to scope->symtab_t
 *
 * when travel ast tree second time, start to truly semantic analysis(e.g type check)
 *
 * @TODO: set up scope list
 */

symtab_t symtab_new(void) {
    symtab_t symtab = (symtab_t)malloc(sizeof(*symtab));
    symtab->table = NULL;
    symtab->num_symbols = 0;
    return symtab;
}

symbol_t symtab_lookup(symtab_t symtab, const char *id) {
    if (symtab == NULL) return NULL;

    for (int i = 0; i < symtab->num_symbols; i++) {
        symbol_t symbol = (symbol_t)stack_get(symtab->table, i);

        if (!strcmp(symbol->id, id)) {
            return symbol;
        }
    }

    return NULL;
}

symtab_t symtab_enter(symtab_t symtab, symbol_t symbol) {
    if (symtab == NULL) return NULL;

    symbol_t exist = symtab_lookup(symtab, symbol->id);

    if (exist != NULL) {
        symtab_failed = 1;
        dragon_report(symbol->loc, "redefined %s", symbol->id);
        return NULL;
    } else {
        stack_push(symtab->table, symbol);
        symtab->num_symbols += 1;
        return symtab;
    }
}
