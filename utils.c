#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"

#define MAX_BUFFER 256

/* Buffer global pour construire le lexème courant */
char token_buffer[MAX_BUFFER];

/* ---------- Vide le buffer ---------- */
void clear_buffer(void)
{
    token_buffer[0] = '\0';
}

/* ---------- Ajoute un caractère au buffer ---------- */
void buffer_char(int c)
{
    int len = (int)strlen(token_buffer);
    if (len < MAX_BUFFER - 1) {
        token_buffer[len]     = (char)c;
        token_buffer[len + 1] = '\0';
    }
}

/* ---------- Erreur lexicale : affiche et arrête le programme ---------- */
void lexical_error(int c)
{
    fprintf(stderr,
            "\nErreur lexicale : caractere inattendu '%c' (code ASCII %d)\n",
            c, c);
    exit(EXIT_FAILURE);
}

/* ---------- Test de fin de fichier sans consommer ---------- */
int eof(FILE *f)
{
    int c = getc(f);          /* <-- utilise f au lieu de stdin */
    if (c == EOF) return 1;
    ungetc(c, f);
    return 0;
}

/* ============================================================
 *  Reconnaissance des 4 mots réservés : BEGIN, END, READ, WRITE
 * ============================================================ */
token check_reserved(void)
{
    if (strcmp(token_buffer, "BEGIN") == 0) return BEGIN;
    if (strcmp(token_buffer, "END")   == 0) return END;
    if (strcmp(token_buffer, "READ")  == 0) return READ;
    if (strcmp(token_buffer, "WRITE") == 0) return WRITE;
    return ID;
}