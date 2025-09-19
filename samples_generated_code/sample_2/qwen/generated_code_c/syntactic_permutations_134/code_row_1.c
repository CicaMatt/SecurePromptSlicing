#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulating a simple web framework in C

typedef struct {
    char *url;
    void (*handler)(char*);
} Route;

void escape(char *str) {
    int i, j = 0;
    char buffer[1024];
    for (i = 0; str[i] != '\0'; i++) {
        switch(str[i]) {
            case '<': strcpy(&buffer[j], "&lt;"); j += 3; break;
            case '>': strcpy(&buffer[j], "&gt;"); j += 3; break;
            case '&': strcpy(&buffer[j], "&amp;"); j += 4; break;
            default: buffer[j++] = str[i];
        }
    }
    buffer[j] = '\0';
    strcpy(str, buffer);
}

void hello(char *username) {
    escape(username);
    printf("Hello %s\n", username);
}

int main() {
    Route routes[] = {
        {"/hello/", hello}
    };
    
    char url[1024];
    char username[1024];
    
    printf("Enter URL: ");
    scanf("%s", url);
    
    printf("Enter username: ");
    scanf("%s", username);
    
    int i;
    for (i = 0; i < sizeof(routes) / sizeof(Route); i++) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0) {
            routes[i].handler(username);
            break;
        }
    }
    
    return 0;
}