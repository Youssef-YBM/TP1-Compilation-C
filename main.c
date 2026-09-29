#include <stdio.h>
#include "tokens.h"

/* ---------- Nom lisible d'un token ---------- */
static const char *token_name(token t)
{
    switch (t) {
        /* littéraux */
        case ID:         return "ID";
        case INTLITERAL: return "INTLITERAL";

        /* opérateurs */
        case PLUSOP:     return "PLUSOP";
        case MINUSOP:    return "MINUSOP";
        case ASSIGNOP:   return "ASSIGNOP";

        /* ponctuation */
        case LPAREN:     return "LPAREN";
        case RPAREN:     return "RPAREN";
        case SEMICOLON:  return "SEMICOLON";
        case COMMA:      return "COMMA";

        /* mots réservés */
        case BEGIN:      return "BEGIN";
        case END:        return "END";
        case READ:       return "READ";
        case WRITE:      return "WRITE";

        /* spécial */
        case SCANEOF:    return "SCANEOF";
        default:         return "?";
    }
}

int main(void)
{
    token t;
    int   n = 0;

    printf("=== Scanner MICRO : entiers + 4 mots reserves ===\n");
    printf("Entrez du code (Ctrl+D pour terminer) :\n\n");

    while ((t = scanner()) != SCANEOF) {
        printf("[%3d]  %-12s  lexeme = \"%s\"\n",
               ++n, token_name(t), token_buffer);
    }

    printf("\n--- Fin : %d token(s) reconnu(s) ---\n", n);
    return 0;
}