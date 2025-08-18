#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void escape(char *str) {
    char buffer[2 * MAX_USERNAME_LENGTH];
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
    static char result[256];
    escape(username);
    snprintf(result, sizeof(result), "Hello %s", username);
    return result;
}

int main() {
    char username[MAX_USERNAME_LENGTH] = "<script>alert('XSS')</script>";
    printf("%s\n", hello(username));
    return 0;
}