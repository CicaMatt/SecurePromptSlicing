#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    void (*handler)(char*);
} Route;

void escape(char *input, char *output) {
    while(*input) {
        if(*input == '<') {
            strcat(output, "&lt;");
        } else if(*input == '>') {
            strcat(output, "&gt;");
        } else if(*input == '&') {
            strcat(output, "&amp;");
        } else {
            strncat(output, input, 1);
        }
        input++;
    }
}

void hello(char *username) {
    char safe_username[256] = "";
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

typedef void (*Handler)(char*);

void route_handler(Handler handler, char *username) {
    handler(username);
}

int main() {
    Route routes[] = {{"hello", hello}, {NULL, NULL}};
    
    char username[100] = "JohnDoe";
    for(int i = 0; routes[i].key != NULL; i++) {
        if(strcmp(routes[i].key, "hello") == 0) {
            route_handler(routes[i].handler, username);
            break;
        }
    }

    return 0;
}