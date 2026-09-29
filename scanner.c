#include <stdio.h>
#include <ctype.h>
#include "tokens.h"

/* ============================================================
 *  scanner() : analyseur lexical du langage MICRO
 *
 *  Règles lexicales :
 *    ID          ::= LETTER (LETTER | DIGIT | '_')*
 *    INTLITERAL  ::= DIGIT+
 *    Mots réservés : BEGIN | END | READ | WRITE
 * ============================================================ */
token scanner(void)
{
    int in_char, c;

    clear_buffer();

    if (eof(stdin))
        return SCANEOF;

    while ((in_char = getc(stdin)) != EOF) {

        /* ---------- 1. Espaces ignorés ---------- */
        if (isspace(in_char))
            continue;

        /* ---------- 2. Identificateur / mot réservé ---------- */
        else if (isalpha(in_char)) {
            buffer_char(in_char);
            for (c = getc(stdin); isalnum(c) || c == '_'; c = getc(stdin))
                buffer_char(c);
            ungetc(c, stdin);
            return check_reserved();
        }

        /* ---------- 3. Littéral entier ---------- */
        else if (isdigit(in_char)) {
            buffer_char(in_char);
            for (c = getc(stdin); isdigit(c); c = getc(stdin))
                buffer_char(c);
            ungetc(c, stdin);
            return INTLITERAL;
        }

        /* ---------- 4. Ponctuation ---------- */
        else if (in_char == '(') return LPAREN;
        else if (in_char == ')') return RPAREN;
        else if (in_char == ';') return SEMICOLON;
        else if (in_char == ',') return COMMA;

        /* ---------- 5. Opérateurs ---------- */
        else if (in_char == '+') return PLUSOP;

        /* ---------- 6. ':' ou ':=' ---------- */
        else if (in_char == ':') {
            c = getc(stdin);
            if (c == '=')
                return ASSIGNOP;
            else {
                ungetc(c, stdin);
                lexical_error(in_char);
                return SCANEOF;
            }
        }

        /* ---------- 7. '-' ou commentaire '--' ---------- */
        else if (in_char == '-') {
            c = getc(stdin);
            if (c == '-') {
                do {
                    in_char = getc(stdin);
                } while (in_char != '\n' && in_char != EOF);
            } else {
                ungetc(c, stdin);
                return MINUSOP;
            }
        }

        /* ---------- 8. Caractère inconnu ---------- */
        else {
            lexical_error(in_char);
            return SCANEOF;
        }
    }

    return SCANEOF;
}