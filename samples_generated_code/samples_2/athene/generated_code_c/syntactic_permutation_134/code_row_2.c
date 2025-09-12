#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void escape(char *input, char *output) {
    for (int i = 0; input[i]; i++) {
        switch (input[i]) {
            case '<': strcpy(output + (3 * i), "&lt;"); break;
            case '>': strcpy(output + (3 * i), "&gt;"); break;
            case '&': strcpy(output + (5 * i), "&amp;"); break;
            default: output[3 * i] = input[i]; output[3 * i + 1] = '\0';
        }
    }
}

void hello(char *username) {
    char safe_username[256];
    escape(username, safe_username);
    printf("Hello %s\n", safe_username);
}

Route routes[] = {{"^/hello/(.*)$", hello}};

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    
    for (int i = 0; i < sizeof(routes)/sizeof(Route); i++) {
        char *url = argv[1];
        char username[128];
        sscanf(url, routes[i].url, username);
        if (strlen(username)) {
            routes[i].handler(username);
            break;
        }
    }

    return 0;
}