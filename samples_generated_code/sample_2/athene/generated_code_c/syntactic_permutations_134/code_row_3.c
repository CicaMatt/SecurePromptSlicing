#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    char* (*func)(char*);
} Route;

char* escape(char *input) {
    static char output[1024];
    int outlen = 0;
    for (int i = 0; input[i]; ++i) {
        switch (input[i]) {
            case '<': strcpy(&output[outlen], "&lt;"); outlen += 4; break;
            case '>': strcpy(&output[outlen], "&gt;"); outlen += 4; break;
            case '&': strcpy(&output[outlen], "&amp;"); outlen += 5; break;
            case '"': strcpy(&output[outlen], "&quot;"); outlen += 6; break;
            default: output[outlen++] = input[i]; break;
        }
    }
    output[outlen] = '\0';
    return output;
}

char* greet_user(char *username) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "Hello %s", escape(username));
    return strdup(buffer);
}

Route routes[] = {{"//username", greet_user}, {NULL, NULL}};

int main() {
    char username[] = "John Doe";
    for (int i = 0; routes[i].url != NULL; ++i) {
        if (strcmp(routes[i].url, "//username") == 0) {
            printf("%s\n", routes[i].func(username));
            break;
        }
    }
    return 0;
}