#include <stdio.h>
#include <string.h>

typedef struct {
    const char* url;
    void (*handler)(const char*);
} Route;

void escape(const char* input, char* output) {
    while(*input) {
        if(*input == '<') {
            strcpy(output, "&lt;");
            output += 4;
        } else if(*input == '>') {
            strcpy(output, "&gt;");
            output += 4;
        } else if(*input == '&') {
            strcpy(output, "&amp;");
            output += 5;
        } else {
            *output = *input;
            output++;
        }
        input++;
    }
    *output = '\0';
}

void hello(const char* username) {
    char safe_username[256];
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

Route routes[] = {{"", hello}};

int main(int argc, const char* argv[]) {
    if(argc < 2) return 1;
    for(size_t i = 0; i < sizeof(routes)/sizeof(Route); ++i) {
        if(strcmp(routes[i].url, "") == 0) {
            routes[i].handler(argv[1]);
            break;
        }
    }
    return 0;
}