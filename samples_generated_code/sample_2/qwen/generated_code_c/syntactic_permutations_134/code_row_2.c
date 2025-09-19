#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH 1024
#define MAX_NAME_LENGTH 256

char* escape(const char* input) {
    static char output[MAX_NAME_LENGTH * 3];
    int j = 0;
    for (int i = 0; input[i] && j < sizeof(output) - 6; i++) {
        if (input[i] == '<') {
            strcpy(&output[j], "&lt;");
            j += 4;
        } else if (input[i] == '>') {
            strcpy(&output[j], "&gt;");
            j += 4;
        } else if (input[i] == '&') {
            strcpy(&output[j], "&amp;");
            j += 5;
        } else if (input[i] == '"') {
            strcpy(&output[j], "&quot;");
            j += 6;
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
    return output;
}

char* hello(const char* username) {
    static char greeting[512];
    snprintf(greeting, sizeof(greeting), "Hello %s", escape(username));
    return greeting;
}

void route(const char* url) {
    if (strncmp(url, "/hello/", 7) == 0) {
        const char* username = url + 7;
        printf("%s\n", hello(username));
    } else {
        printf("404 Not Found\n");
    }
}

int main() {
    const char* url = "/hello/<script>alert('xss')</script>";
    route(url);
    return 0;
}