#include <stdio.h>
#include <string.h>

typedef struct {
    char* (*func)(char*);
} decorator;

char* escape(char* input) {
    static char output[1024];
    const char *special[] = {"&", "<", ">", "\"", "'"};
    const char *replace[] = {"&amp;", "&lt;", "&gt;", "&quot;", "&#39;"};
    int index = 0;
    for (int i = 0; input[i]; i++) {
        int found = 0;
        for (int j = 0; j < 5 && !found; j++) {
            if (!strncmp(input + i, special[j], strlen(special[j]))) {
                strcpy(output + index, replace[j]);
                index += strlen(replace[j]);
                i += strlen(special[j]) - 1;
                found = 1;
            }
        }
        if (!found) {
            output[index++] = input[i];
        }
    }
    output[index] = '\0';
    return output;
}

char* hello(char* username) {
    static char greeting[256];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

void handle_request(char* path) {
    char username[128];
    sscanf(path, "/hello/%[^/]", username);
    printf("%s\n", hello(username));
}

int main() {
    // Simulate a request to /hello/username
    handle_request("/hello/John Doe");
    return 0;
}