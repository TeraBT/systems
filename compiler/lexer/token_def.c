#include "token_def.h"

const char *map(token_t token) {
    switch (token) {
    case END:
        return "END";
    case IF:
        return "IF";
    case ELSE:
        return "ELSE";
    case TYPE_INT:
        return "TYPE_INT";
    case VAR:
        return "VAR";
    case INT:
        return "INT";
    case ADD:
        return "ADD";
    case SUB:
        return "SUB";
    case MUL:
        return "MUL";
    case EQ:
        return "EQ";
    case EQEQ:
        return "EQEQ";
    case DIV:
        return "DIV";
    case LPAR:
        return "LPAR";
    case RPAR:
        return "RPAR";
    case LBRAC:
        return "LBRAC";
    case RBRAC:
        return "RBRAC";
    case SEMCOL:
        return "SEMCOL";
    default:
        return "UNDEF";
    }
}
