/*!
 * \file Expr.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_EXPR_H
#define AST_EXPR_H

#include "ast/common.h"
#include "ast/Type.h"
#include "ast/Const.h"
#include "ast/Def.h"

/*
 * @brief: kind of expr_t
 */
} expr_kind_t;

/*
 * @interface: expr_t
 */
typedef struct expr {
    expr_kind_t kind;           ///< EXPR_BASIC
    yyltype loc;
    scope_t env;
} *expr_t;

/*
 * @brief: kind of expr_prim_t
 */
} expr_prim_kind_t;

/*
 * @interface: expr_prim_t
 */
typedef struct expr_prim {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
} *expr_prim_t;

/*
 * @implements: expr_prim_ident_t
 */
typedef struct expr_prim_ident {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
    string id;
} *expr_prim_ident_t;

/*
 * @implements: expr_prim_const_t
 */
typedef struct expr_prim_const {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
    Const *const_val;
} *expr_prim_const_t;

/*
 * @implements: expr_prim_readint_t/expr_prim_readline_t
 */
typedef struct _expr_prim_read_ {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
} *expr_prim_read_t;

/*
 * @implements: expr_prim_newclass_t
 */
typedef struct _expr_prim_newclass_ {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
    string id;
    List<actual_t> actuals;             ///< list_t <actual_t>
} *expr_prim_newclass_t;

/*
 * @implements: expr_prim_newarray_t
 */
typedef struct _expr_prim_newarray_ {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_prim_kind_t sub_kind;
    type_t type;
    expr_t length;
} *expr_prim_newarray_t;

/*
 * @brief: kind of expr_left_t
 */
} expr_left_kind_t;

/*
 * @interface: expr_left_t
 */
typedef struct expr_left {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
} *expr_left_t;

/*
 * @implements: expr_left_this_t
 */
typedef struct expr_left_this {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
} *expr_left_this_t;

/*
 * @implements: expr_left_index_t
 */
typedef struct expr_left_index {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
    expr_left_t array;
    expr_t index;
} *expr_left_index_t;

/*
 * @implements: expr_left_class_field_t
 */
typedef struct expr_left_class_field {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
    expr_left_t left;
    string field_id;
} *expr_left_class_field_t;

/*
 * @implements: expr_left_class_call_t
 */
typedef struct expr_left_class_call {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
    expr_left_t left;
    string field_id;
    List<actual_t> actuals;         ///< list_t <actual_t>
} *expr_left_class_call_t;

/*
 * @implements: expr_left_func_call_t
 */
typedef struct expr_left_func_call {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
    char *id;
    List<actual_t> actuals;         ///< list_t <actual_t>
} *expr_left_func_call_t;

/*
 * @implements: expr_left_anony_call_t
 */
typedef struct expr_left_anony_call {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_kind_t sub_kind;
    func_anony_def_t func_body;
    List<actual_t> actuals;         ///< list_t <actual_t>
} *expr_left_anony_call_t;

/*
 * @brief: kind of expr_unary_t
 */
} expr_unary_kind_t;

/*
 * @implements: expr_unary_this_t/expr_unary_plus_t/expr_unary_minus_t/expr_unary_not_t
 */
typedef struct expr_unary {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_unary_kind_t sub_kind;
    struct expr_unary *body;
} *expr_unary_t;

/*
 * @brief: kind of expr_mul_t
 */
} expr_mul_kind_t;

/*
 * @implements: expr_mul_mul_t/expr_mul_sub_t/expr_mul_mod_t
 */
typedef struct expr_mul {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_mul_kind_t sub_kind;
    struct expr_mul *left;
    expr_unary_t right;
} *expr_mul_t;

/*
 * @brief: kind of expr_add_t
 */
} expr_add_kind_t;

/*
 * @implements: expr_add_add_t/expr_add_sub_t
 */
typedef struct expr_add {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_add_kind_t sub_kind;
    struct expr_add *left;
    expr_mul_t right;
} *expr_add_t;

/*
 * @brief: kind of expr_cmp_t
 */
} expr_cmp_kind_t;

/*
 * @implements: expr_cmp_l_t/expr_cmp_g_t/expr_cmp_le_t/expr_cmp_ge_t
 */
typedef struct expr_cmp {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_cmp_kind_t sub_kind;
    struct expr_cmp *left;
    expr_add_t right;
} *expr_cmp_t;

/*
 * @brief: kind of expr_eq_t
 */
} expr_eq_kind_t;

/*
 * @implements: expr_eq_eq_t/expr_eq_ne_t
 */
typedef struct expr_eq {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_eq_kind_t sub_kind;
    struct expr_eq *left;
    expr_cmp_t right;
} *expr_eq_t;

/*
 * @implements: expr_and_t
 */
typedef struct expr_and {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    struct expr_and *left;
    expr_eq_t right;
} *expr_and_t;

/*
 * @implements: expr_or_t
 */
typedef struct expr_or {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    struct expr_or *left;
    expr_and_t right;
} *expr_or_t;

/*
 * @implements: expr_assign_t
 */
struct expr_assign {
    expr_kind_t kind;
    yyltype loc;
    scope_t env;
    expr_left_t left;
    expr_assign_t right;
};

/*
 * @implements: expr_bool_t
 */
typedef struct expr_bool {
    expr_kind_t kind;           ///< EXPR_BOOL
    yyltype loc;
    scope_t env;
    expr_t body;
} *expr_bool_t;

/*
 * @brief: create prim_expr node
 */
expr_t expr_prim_ident_new(expr_kind_t kind, expr_prim_kind_t sub_kind, yyltype loc, string id);
expr_t expr_prim_const_new(expr_kind_t kind, expr_prim_kind_t sub_kind, yyltype loc, Const *const_val);
expr_t expr_prim_read_new(expr_kind_t kind, expr_prim_kind_t sub_kind, yyltype loc);
expr_t expr_prim_newclass_new(expr_kind_t kind, expr_prim_kind_t sub_kind, yyltype loc, string id, List<actual_t> actuals);
expr_t expr_prim_newarray_new(expr_kind_t kind, expr_prim_kind_t sub_kind, yyltype loc, type_t type, expr_t length);

/*
 * @brief: create left_expr node
 */
expr_t expr_left_this_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc);
expr_t expr_left_index_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc, expr_left_t array, expr_t index);
expr_t expr_left_class_field_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc, expr_left_t left, string field_id);
expr_t expr_left_class_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc, expr_left_t left, string field_id, List<actual_t> actuals);
expr_t expr_left_func_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc, char *id, List<actual_t> actuals);
expr_t expr_left_anony_call_new(expr_kind_t kind, expr_left_kind_t sub_kind, yyltype loc, func_anony_def_t func_body, List<actual_t> actuals);

/*
 * @brief: create unary_expr node
 */
expr_t expr_unary_new(expr_kind_t kind, expr_unary_kind_t sub_kind, yyltype loc, expr_unary_t body);

/*
 * @brief: create mul_expr node
 */
expr_t expr_mul_new(expr_kind_t kind, expr_mul_kind_t sub_kind, yyltype loc, expr_mul_t left, expr_unary_t right);

/*
 * @brief: create add_expr node
 */
expr_t expr_add_new(expr_kind_t kind, expr_add_kind_t sub_kind, yyltype loc, expr_add_t left, expr_mul_t right);

/*
 * @brief: create cmp_expr node
 */
expr_t expr_cmp_new(expr_kind_t kind, expr_cmp_kind_t sub_kind, yyltype loc, expr_cmp_t left, expr_add_t right);

/*
 * @brief: create eq_expr node
 */
expr_t expr_eq_new(expr_kind_t kind, expr_eq_kind_t sub_kind, yyltype loc, expr_eq_t left, expr_cmp_t right);

/*
 * @brief: create and_expr node
 */
expr_t expr_and_new(expr_kind_t kind, yyltype loc, expr_and_t left, expr_eq_t right);

/*
 * @brief: create or_expr node
 */
expr_t expr_or_new(expr_kind_t kind, yyltype loc, expr_or_t left, expr_and_t right);

/*
 * @brief: create assign_expr node
 */
expr_t expr_assign_new(expr_kind_t kind, yyltype loc, expr_left_t left, expr_assign_t right);

/*
 * @brief: create bool_expr node
 */
expr_bool_t expr_bool_new(expr_kind_t kind, yyltype loc, expr_t body);

#endif /* !AST_EXPR_H */
