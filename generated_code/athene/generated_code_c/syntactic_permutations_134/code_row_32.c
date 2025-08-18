#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *input, char *output) {
    for (int i = 0; i < strlen(input); i++) {
        switch (input[i]) {
            case '<': strcpy(output + (i * 4), "&lt;"); break;
            case '>': strcpy(output + (i * 4), "&gt;"); break;
            case '&': strcpy(output + (i * 5), "&amp;"); break;
            case '"': strcpy(output + (i * 6), "&quot;"); break;
            case '\'': strcpy(output + (i * 6), "&#39;"); break;
            default: output[i] = input[i]; break;
        }
    }
    output[strlen(input) * 6] = '\0'; // Worst case scenario, each char could be expanded to 6 chars
}

char* hello(char *username) {
    static char response[200];
    char escaped_username[MAX_USERNAME_LENGTH * 6];
    escape(username, escaped_username);
    snprintf(response, sizeof(response), "Hello %s", escaped_username);
    return response;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    printf("%s\n", hello(argv[1]));
    return 0;
}