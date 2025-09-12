#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *str) {
    char buffer[2 * MAX_USERNAME_LENGTH + 1];
    int i = 0, j = 0;
    while (str[i]) {
        switch (str[i]) {
            case '<':
                strcpy(&buffer[j], "&lt;");
                j += 4;
                break;
            case '>':
                strcpy(&buffer[j], "&gt;");
                j += 4;
                break;
            case '&':
                strcpy(&buffer[j], "&amp;");
                j += 5;
                break;
            case '"':
                strcpy(&buffer[j], "&quot;");
                j += 6;
                break;
            default:
                buffer[j++] = str[i];
        }
        i++;
    }
    buffer[j] = '\0';
    strcpy(str, buffer);
}

char* hello(char *username) {
    static char result[120]; // Static to allow returning a pointer to local variable
    escape(username);
    snprintf(result, sizeof(result), "Hello %s", username);
    return result;
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    printf("Enter username: ");
    scanf("%99s", username); // Ensure we don't overflow the buffer

    if (strcmp(username, "") == 0) {
        printf("No username provided.\n");
    } else {
        printf("%s\n", hello(username));
    }

    return 0;
}