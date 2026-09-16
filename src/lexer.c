#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "token.h"

void token_list_init(token_list* list)
{
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

void token_list_push(token_list* list, token tok)
{
    if(list->count == list->capacity)
    {
	size_t new_size = list->capacity ? list->capacity * 2 : 64;
	token* p = realloc(list->items, new_size * sizeof(token));
	if(!p)
	{
	    printf("ERROR: system out of memory\n");
	    exit(1);
	}
	list->items = p;
	list->capacity = new_size;
    }
    list->items[list->count++] = tok;
}

void token_list_free(token_list* list)
{
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int is_ident_start(char c)
{
    return isalpha((unsigned char)c) || c == '_';
}

static int is_ident_char(char c)
{
    return isalnum((unsigned char)c) || c == '_';
}

static token_kind keyword_kind(const char* start, size_t len)
{
    if(len == 6 && strcmp(start, "struct") == 0)   return TOK_KEYWORD_STRUCT;
    if(len == 8 && strcmp(start, "operator") == 0) return TOK_KEYWORD_OPERATOR;
    return TOK_IDENT;
}

void lex(const char* src, token_list* out)
{
    token_list_init(out);
    int line = 1;
    const char* p = src;

    while(*p)
    {
	//Whitespace
	
	//comments
	

    }

    token eof = {TOK_EOF, p, 0, 1};
    token_list_push(out, eof);
}
