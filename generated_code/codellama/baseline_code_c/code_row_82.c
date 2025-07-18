#include <stdio.h>  // C standard library for input and output
#include <stdlib.h> // C standard library for strtol(), strtoll(), strtof(), and strtod() functions
#include <string.h> // C standard library for string operations

#include "mjson.h"  // mJSON library for JSON parsing

#define BUFFER_SIZE 1024 * 16

int main(void) {
    // Define variables for web app, route, and payload parameter
    struct mjson_app *app;
    struct mjson_tok *route, *payload;
    
    // Initialize memory for web app
    if ((app = malloc(sizeof(struct mjson_app))) == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Initialize variables to empty values
    memset(app, 0, sizeof(*app));
    route = payload = NULL;

    // Read in user input for payload parameter until EOF (Ctrl + D)
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        app->buffer = buffer;
        app->ptr = 0;
        
        // Get the route and payload parameter from user input
        if ((route = mjson_find(app, "api")) == NULL) {
            printf("Invalid API: %s\n", buffer);
            continue;
        }
        if (route->type != MJSON_TOK_STRING || strcmp(route->ptr, "api") != 0) {
            printf("Invalid API: %s\n", route->ptr);
            continue;
        }
        payload = mjson_find(app, "payload");
        
        // Load the payload parameter into a dictionary
        struct mjson_dict *dict;
        if ((dict = mjson_dict_create(app)) == NULL) {
            printf("Failed to create JSON dictionary\n");
            continue;
        }
        if (mjson_parse(payload, dict, app->buffer, MJSON_TOK_NONE)) {
            printf("Failed to parse payload: %s\n", buffer);
            mjson_dict_free(app, dict);
            continue;
        }
        
        // Get the name value from the dictionary
        struct mjson_tok *name = mjson_find(dict, "name");
        if (name == NULL || name->type != MJSON_TOK_STRING) {
            printf("Invalid payload: %s\n", buffer);
            mjson_dict_free(app, dict);
            continue;
        }
        
        // Print the name value from the dictionary
        printf("%s\n", name->ptr);
    }
    
    return 0;
}