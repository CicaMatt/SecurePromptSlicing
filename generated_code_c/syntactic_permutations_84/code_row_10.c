#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "yaml.h"
    
    int main(int argc, char *argv[]) {
        const char *payload = NULL;
        yaml_parser_t parser;
        yaml_event_t event;
        char *type = NULL;
        if(!(payload = getenv("PAYLOAD"))) {
            fprintf(stderr, "No payload parameter found!\n");
            return 1;
        }
        
        yaml_parser_initialize(&parser);
        yaml_parser_set_input_string(&parser, payload, strlen(payload));
        
        while(yaml_parser_parse(&parser, &event)) {
            if(event.type == YAML_MAPPING_START_EVENT) {
                while(yaml_parser_parse(&parser, &event)) {
                    if(event.type == YAML_SCALAR_EVENT) {
                        type = (char *) event.data.scalar.value;
                    }
                }
            }
        }
        
        if(!strcmp(type, "Create")) {
            fprintf(stderr, "Error: Payload is a create request!\n");
            return 1;
        }
        
        yaml_event_delete(&event);
        yaml_parser_delete(&parser);
    }