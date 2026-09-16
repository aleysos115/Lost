#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <stddef.h>

typedef enum 
{
    TOK_EOF,
    TOK_IDENT,		   /* if, else... */
    TOK_NUMBER,		   /* 123 */
    TOK_STRING,            /* "hello" */
    TOK_CHAR,		   /* 'a' */
    TOK_KEYWORD_STRUCT,    /* struct */
    TOK_KEYWORD_OPERATOR,  /* operator */
    TOK_LBRACE,   	   /* { */
    TOK_RBRACE,   	   /* } */
    TOK_LPAREN,   	   /* ( */
    TOK_RPAREN,   	   /* ) */
    TOK_SEMI,     	   /* ; */
    TOK_COMMA,    	   /* , */
    TOK_DOT,      	   /* . */
    TOK_PLUS,     	   /* + */
    TOK_MINUS,    	   /* - */
    TOK_STAR,     	   /* * */
    TOK_SLASH,    	   /* / */
    TOK_ASSIGN,   	   /* = */
    TOK_AMP,      	   /* & */
    TOK_EXCLAM		   /* ! */
} token_kind;

typedef struct 
{
    token_kind kind;
    const char* start;
    size_t size;
    unsigned int line;
} token; 

typedef struct
{
    token* items;
    size_t count;
    size_t capacity;
} token_list;

#endif
