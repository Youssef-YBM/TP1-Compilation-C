#ifndef TOKENS_H
#define TOKENS_H

#include <stdio.h>

/* ============================================================
 *  Enumération des tokens du langage MICRO
 * ============================================================ */
typedef enum token {
    /* ----- Littéraux ----- */
    ID,              /* identificateur : commence par lettre,
                        suivi de lettres / chiffres / '_' */
    INTLITERAL,      /* entier : suite de chiffres          */

    /* ----- Opérateurs ----- */
    PLUSOP,          /* +    */
    MINUSOP,         /* -    */
    ASSIGNOP,        /* :=   */

    /* ----- Ponctuation ----- */
    LPAREN,          /* (    */
    RPAREN,          /* )    */
    SEMICOLON,       /* ;    */
    COMMA,           /* ,    */

    /* ----- Mots réservés (4) ----- */
    BEGIN,
    END,
    READ,
    WRITE,

    /* ----- Spécial ----- */
    SCANEOF          /* fin de fichier */
} token;

/* ============================================================
 *  Prototypes
 * ============================================================ */
extern token scanner(void);

extern void  clear_buffer(void);
extern void  buffer_char(int c);
extern token check_reserved(void);
extern void  lexical_error(int c);
extern int   eof(FILE *f);

extern char token_buffer[];   /* défini dans utils.c */

#endif /* TOKENS_H */