#ifndef TOKEN_DEF_H
#define TOKEN_DEF_H

typedef enum {
    END,

    IF,
    ELSE,

    TYPE_INT,
    VAR,

    INT,

    ADD,
    SUB,
    MUL,
    DIV,

    EQ,

    EQEQ,

    LPAR,
    RPAR,
    LBRAC,
    RBRAC,

    SEMCOL
} token_t;

const char *map(token_t token);

#endif
