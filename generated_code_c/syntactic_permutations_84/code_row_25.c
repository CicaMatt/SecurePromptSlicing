#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <yaml.h>

    typedef struct {
        char *type;
        char *value;
    } Request;

    int main() {
        // Initialize the web application
        // Listen on port 5000

        // Accept a request and parse it into a Request object

        if (request.payload == NULL) {
            return "Error: Missing payload";
        }

        yaml_document_t document;
        yaml_parser_t parser;
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(
            &parser, request.payload, strlen(request.payload));
        yaml_parser_load(&parser, &document);

        if (strcmp(yaml_get_type(), "Create") != 0) {
            return "Error: Only create requests are accepted";
        }

        // Process the request based on its type and value

        return "Request processed successfully";
    }