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
	if(*p == '\n')
	{
	    line++;
	    p++;
	    continue;
	}

	if(isspace((unsigned char)*p))
	{
	    p++;
	    continue;
	}
	
	//comments
	if(p[0] == '/' && p[1] == '/')
	{
	    while(*p && *p != '\n')
	    {
		p++;
	    }
	    continue;
	}

	if(p[0] == '*' && p[1] == '/')
	{
	    p++;
	    while(*p && p[0] != '/' && p[1] != '*')
	    {
		p++;
	    }
	    continue;
	}
	
	const char* start = p;

	//ident
	if(is_ident_start(*p))
	{
	    while(is_ident_char(*p))
	    {
		p++;
	    }
	    size_t len = (size_t)(p - start);
	    token t = {keyword_kind(start, len), start, len, line};
	    token_list_push(out, t);
	    continue;
	}

	//number
	if(isdigit((unsigned char)*p))
	{
	    while(isdigit((unsigned char)*p))
	    {
		p++;
	    }
	    size_t len = (size_t)(p - start);
	    token t = {TOK_NUMBER, start, len, line};
	    token_list_push(out, t);
	    continue;
	}

	//string literal
	if(*p == '"')
	{
	    p++;
	    while(*p && *p != '"')
	    {
		p++;
	    }
	    if(*p == '"')
		p++;
	    size_t len = (size_t)(p - start);
	    token t = {TOK_STRING, start, len, line};
	    token_list_push(out, t);
	    continue;
	}

	if(*p == '\'')
	{
	    p++;
	    while(*p && *p != '\'')
	    {
		p++;
	    }
	    if(*p == '\'')
		p++;
	    size_t len = (size_t)(p - start);
	    token t = {TOK_CHAR, start, len, line};
	    token_list_push(out, t);
	    continue;
	}

	token_kind kind;
	switch(*p)
	{
	    case '{':
		kind = TOK_LBRACE;
		break;
	    case '}':
		kind = TOK_RBRACE;
		break;
	    case '(':
		kind = TOK_LPAREN;
		break;
	    case ')':
		kind = TOK_RPAREN;
		break;
	    case '[':
		kind = TOK_LBRACKET;
		break;
	    case ']':
		kind = TOK_RBRACKET;
		break;
	    case ';':
		kind = TOK_SEMI;     	   
		break;
	    case ':':
		kind = TOK_COLON;     	   
		break;
	    case ',':
		kind = TOK_COMMA;
		break;
	    case '.':
		kind = TOK_DOT;
		break;
	    case '+':
		kind = TOK_PLUS;
		break;
	    case '-':
		kind = TOK_MINUS;
		break;
	    case '*':
		kind = TOK_STAR;
		break;
	    case '/':
		kind = TOK_SLASH;
		break;
	    case '=':
		kind = TOK_ASSIGN;
		break;
	    case '&':
		kind = TOK_AMP;
		break;
	    case '!':
		kind = TOK_EXCLAM;
		break;
	    case '#':
		kind = TOK_HASH;
		break;
	    default:
		printf("line %d, unexpected character '%c'\n", line, *p);
		p++;
		continue;
	}
	p++;
	token t = {kind, start, 1, line};
	token_list_push(out, t);
    }

    token eof = {TOK_EOF, p, 0, 1};
    token_list_push(out, eof);
}
