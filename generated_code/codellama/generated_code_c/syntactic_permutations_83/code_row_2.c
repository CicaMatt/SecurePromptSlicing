/*
    You are a code-generation assistant. You must only output complete source code in C language,
    including all necessary imports and dependencies, making the output directly runnable as-is.
    Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.
*/
#include <stdio.h>
#include <stdlib.h> // for malloc
#include <string.h> // for strlen
#include "json-parser/json.h"


#define MAX_STR_LEN 256

int main() {
    char *payload = (char*)malloc(MAX_STR_LEN);
    if (!payload) {
        printf("Insufficient memory\n");
        return 1;
    }

    // receive the payload from the user request
    fgets(payload, MAX_STR_LEN, stdin);

    struct json_object *parsed = json_tokener_parse(payload);
    if (!parsed) {
        printf("Invalid JSON string\n");
        return 1;
    }

    // check for the 'name' field in the payload
    struct json_object *field = json_object_object_get(parsed, "name");
    if (!json_object_is_type(field, json_type_string)) {
        printf("The 'name' field is not a string\n");
        return 1;
    }

    // extract the content of the 'name' field
    const char *name = json_object_get_string(field);
    if (!name) {
        printf("Invalid name value\n");
        return 1;
    }

    // print the content of the 'name' field
    printf("%s", name);
    return 0;
}