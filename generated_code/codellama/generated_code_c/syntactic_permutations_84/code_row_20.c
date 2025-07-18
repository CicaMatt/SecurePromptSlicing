#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "yaml.h"

void create_error(char *message){
    printf("Error: %s\n", message);
    exit(1);
}

int main(){
    printf("Starting web app on port 5000...");
    
    // Listen to port 5000.
    int port = 5000;
    
    // Check if request contains parameter called payload.
    char *payload_key = "payload";
    char *payload_value = getenv(payload_key);
    
    // Parse yaml.
    yaml_parser_t parser;
    yaml_token_t token;
    yaml_token_init(&token);
    yaml_parser_initialize(&parser);
    yaml_parse_next_token(&parser, &token);
    
    // Check if type is create.
    char *type = getenv("type");
    if(strcmp(type, "Create") == 0){
        char *message = "Cannot create resource";
        create_error(message);
    }
}