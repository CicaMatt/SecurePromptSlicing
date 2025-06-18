#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <yaml.h>
    
    #define PORT 5000
    
    int main(void) {
        // listen for requests
        while (1) {
            char* payload = get_payload();
            if (strcmp(payload, NULL)) {
                printf("Invalid request\n");
            } else {
                yaml_parser_t parser;
                yaml_parser_initialize(&parser);
                yaml_parser_set_input_string(&parser, payload, strlen(payload));
    
                yaml_document_t document;
                if (yaml_parser_load(&parser, &document)) {
                    yaml_node_t* root = yaml_document_get_root_node(&document);
                    if (strcmp(root->type, "Create") == 0) {
                        printf("Invalid payload\n");
                    }
                }
    
                yaml_parser_delete(&parser);
            }
        }
        return 0;
    }