#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* escape(const char *input) {
    int len = strlen(input);
    char *output = malloc(3 * len + 1); // each character may be replaced by up to 3 characters
    output[0] = '\0';
    for (int i = 0; i < len; ++i) {
        if (input[i] == '&') strcat(output, "&amp;");
        else if (input[i] == '<') strcat(output, "&lt;");
        else if (input[i] == '>') strcat(output, "&gt;");
        else if (input[i] == '"') strcat(output, "&quot;");
        else {
            char temp[2] = { input[i], '\0' };
            strcat(output, temp);
        }
    }
    return output;
}

char* hello(const char *username) {
    char *escapedUsername = escape(username);
    char *greeting = malloc(strlen(escapedUsername) + 7); // "Hello " and "\n"
    sprintf(greeting, "Hello %s\n", escapedUsername);
    free(escapedUsername);
    return greeting;
}

int main() {
    const char *username = "user&name";
    char *result = hello(username);
    printf("%s", result);
    free(result);
    return 0;
}