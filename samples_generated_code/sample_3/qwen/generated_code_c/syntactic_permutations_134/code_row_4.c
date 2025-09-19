#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50

void escape(const char *input, char *output) {
    int i = 0;
    int j = 0;
    while (input[i] != '\0') {
        switch (input[i]) {
            case '<': 
                strcpy(output + j, "&lt;");
                j += 4;
                break;
            case '>': 
                strcpy(output + j, "&gt;");
                j += 4;
                break;
            case '&': 
                strcpy(output + j, "&amp;");
                j += 5;
                break;
            case '"': 
                strcpy(output + j, "&quot;");
                j += 6;
                break;
            default:
                output[j++] = input[i];
        }
        i++;
    }
    output[j] = '\0';
}

void hello(const char *username) {
    char safe_username[2 * MAX_USERNAME_LENGTH + 1];
    escape(username, safe_username);
    printf("Hello, %s!", safe_username);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "/hello/") != 0) {
        fprintf(stderr, "Usage: %s /hello/ <username>\n", argv[0]);
        return EXIT_FAILURE;
    }
    hello(argv[2]);
    return EXIT_SUCCESS;
}