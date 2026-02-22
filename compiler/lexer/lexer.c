#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token_def.h"

const char *buffer_in_mem(FILE *in);

const token_t *lex(const char *input);
bool starts_with(const char *input, const char *prefix);

void print(const token_t *token_arr);
void pretty_print(const token_t *token_arr);

int main(int argc, char **argv) {

    FILE *in = stdin;
    const char *input = nullptr;

    if (argc == 2) {
        input = argv[1];
    } else {
        input = buffer_in_mem(in);
    }

    const token_t *token_arr = lex(input);

    printf("%s", input);

    print(token_arr);

    pretty_print(token_arr);

    return 0;
}

const char *buffer_in_mem(FILE *in) {
    char *input = nullptr;

    size_t cap = 0;
    size_t size = 0;

    char c;
    while ((c = fgetc(in)) != EOF) {
        if (size + 1 >= cap) {
            cap = cap ? cap * 2 : 1024;
            input = realloc(input, cap * sizeof(*input));
        }
        input[size++] = (char)c;
    }

    input[size] = '\0';
    return input;
}

const token_t *lex(const char *input) {
    token_t *token_arr = malloc(strlen(input) * sizeof(*token_arr));
    void *head_ptr = token_arr;

    while (*input) {
        size_t step_size = 1;

        if (isalpha(*input)) {
            token_t keywords[] = {IF, ELSE, TYPE_INT};
            const char *keyword_values[] = {"if", "else", "int"};

            bool matched = 0;
            for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]);
                 i++) {
                if (starts_with(input, keyword_values[i])) {
                    *token_arr++ = keywords[i];
                    step_size = strlen(keyword_values[i]);
                    matched = true;
                    break;
                }
            }
            if (!matched) {
                *token_arr++ = VAR;
            }
        } else if (isdigit(*input)) {
            *token_arr++ = INT;
        } else if (*input == '+') {
            *token_arr++ = ADD;
        } else if (*input == '-') {
            *token_arr++ = SUB;
        } else if (*input == '*') {
            *token_arr++ = MUL;
        } else if (*input == '/') {
            *token_arr++ = DIV;
        } else if (*input == '=') {
            if (*(input + 1) == '=') {
                *token_arr++ = EQEQ;
                step_size = 2;
            } else {
                *token_arr++ = EQ;
            }
        } else if (*input == '(') {
            *token_arr++ = LPAR;
        } else if (*input == ')') {
            *token_arr++ = RPAR;
        } else if (*input == '{') {
            *token_arr++ = LBRAC;
        } else if (*input == '}') {
            *token_arr++ = RBRAC;
        } else if (*input == ';') {
            *token_arr++ = SEMCOL;
        } else if (1) {
            // to be continued...
        }

        input += step_size;
    }

    *token_arr = END;
    return head_ptr;
}

bool starts_with(const char *input, const char *prefix) {
    size_t prefix_len = strlen(prefix);
    size_t input_len = strlen(input);

    if (prefix_len > input_len) {
        return false;
    }

    for (size_t i = 0; i < prefix_len; i++) {
        if (input[i] != prefix[i]) {
            return false;
        }
    }

    return true;
}

void print(const token_t *token_arr) {
    while (*token_arr != END) {
        printf("%d ", *token_arr++);
    }

    printf("%d\n", *token_arr);
}

void pretty_print(const token_t *token_arr) {
    while (*token_arr != END) {
        printf("%s ", map(*token_arr++));
    }
    printf("%s\n", map(*token_arr));
}
