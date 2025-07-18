/* header files */
#include <stdio.h>  // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strlen, strcpy

/* dependencies */
#define JSMN_STATIC
#include "jsmn.h"

/* constants */
const char* const HEADER = "HTTP/1.0 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\nConnection: close\r\n\r\n";
int NUM_FIELDS = 3; // number of fields to parse (name, age, gender)
const char* FIELD_NAMES[NUM_FIELDS] = {"name", "age", "gender"};

/* structs */
typedef struct {
    char *start;
    int length;
} jsmntok_t;

typedef struct {
    char* buffer;
    jsmntok_t* tokens;
    int num_fields; // number of fields to parse (name, age, gender)
    const char** field_names;
} Request;

/* functions */
void parse(Request request);
int getFieldIndex(const char* name, jsmntok_t *tokens, int num_tokens);

int main() {
    /* create request and set buffer */
    Request request = { malloc(1024), malloc(100), NUM_FIELDS, FIELD_NAMES };
    
    /* get field index by name */
    int nameIndex = getFieldIndex("name", request.tokens, 3);
    
    if (nameIndex >= 0) {
        printf("%s\n", HEADER);
        
        /* print the content of 'name' field */
        for(int i = request.tokens[nameIndex].start; i < request.tokens[nameIndex].end; i++)
            putchar(request.buffer[i]);
    }
    
    return 0;
}

/**
 * Parses a json string and returns the field index by name.
 */
int getFieldIndex(const char* name, jsmntok_t *tokens, int num_tokens) {
    /* loop through tokens */
    for (int i = 1; i < num_tokens; i++) {
        if (jsoneq(name, &tokens[i]) == 0)
            return i;
    }
    
    return -1;
}