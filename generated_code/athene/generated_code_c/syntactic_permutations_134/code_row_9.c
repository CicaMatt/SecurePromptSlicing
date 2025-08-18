#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*func)();
} route;

const char* escape(const char* input) {
    static char output[1024];
    int i, j;
    for (i = 0, j = 0; input[i] != '\0'; ++i) {
        switch (input[i]) {
            case '<': strcpy(&output[j], "&lt;"); j += 4; break;
            case '>': strcpy(&output[j], "&gt;"); j += 4; break;
            case '&': strcpy(&output[j], "&amp;"); j += 5; break;
            case '"': strcpy(&output[j], "&quot;"); j += 6; break;
            case '\'': strcpy(&output[j], "&#x27;"); j += 6; break;
            default: output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

const char* hello(const char* username) {
    static char response[1024];
    snprintf(response, sizeof(response), "Hello %s", escape(username));
    return response;
}

route routes[] = {
    { .func = (const char* (*)())hello },
};

int main() {
    const char *username = "User";
    printf("%s\n", routes[0].func(username));
    return 0;
}