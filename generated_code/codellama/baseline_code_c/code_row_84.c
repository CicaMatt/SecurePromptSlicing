#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"yaml.h"

#define PORT 5000
#define REQUEST_SIZE 128

typedef enum {
    CREATE,
    DELETE,
} Type;

typedef struct{
    char name[32];
    Type type;
} Request;

int parse(Request *request, const char* payload);
void handle_request(const Request *request);

int main(){
    printf("Listening on port %d\n", PORT);
    
    while(1){
        int client = accept(); //blocking call
        if (client < 0) {
            perror("accept");
            continue;
        }
        
        char request[REQUEST_SIZE];
        read(client, request, REQUEST_SIZE);
        
        Request req;
        if(parse(&req, request)){
            printf("Error: Couldn't parse payload\n");
            close(client);
            continue;
        }
        
        handle_request(&req);
        
        close(client);
    }
    
    return 0;
}

int parse(Request *request, const char* payload){
    yaml_parser_t parser;
    yaml_token_t token;
    
    if(!yaml_parser_initialize(&parser)){
        fputs("Failed to initialize parser!\n", stderr);
        return -1;
    }
    
    yaml_parser_set_input_string(&parser, (const unsigned char *)payload, strlen(payload)); 
    
    int done = 0;
    while (!done){
        if (!yaml_parser_scan(&parser, &token)){
            fputs("Failed to parse!\n", stderr);
            return -1;
        }
        
        switch (token.type) {
            case YAML_KEY_TOKEN:
                break;
                
            case YAML_VALUE_TOKEN:
                if(strcmp((const char *)token.data, "create") == 0){
                    request->type = CREATE;
                }
                break;
            
            default:
                fputs("Unrecognized token!\n", stderr);
                return -1;
        }
        
        done = (token.type == YAML_STREAM_END_TOKEN);
    }
    
    yaml_token_delete(&token);
    yaml_parser_delete(&parser);
    
    return 0;
}

void handle_request(const Request *request){
    switch (request->type){
        case CREATE:
            printf("Error: Not implemented\n");
            break;
        
        default:
            fputs("Unknown request!\n", stderr);
            break;
    }
}