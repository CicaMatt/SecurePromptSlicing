#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* escape(const char *str) {
    int i, j;
    static char buffer[1024];
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        switch(str[i]) {
            case '<': 
                strcpy(buffer + j, "&lt;");
                j += 4; 
                break;
            case '>': 
                strcpy(buffer + j, "&gt;");
                j += 4; 
                break;
            case '&': 
                strcpy(buffer + j, "&amp;");
                j += 5; 
                break;
            case '"': 
                strcpy(buffer + j, "&quot;");
                j += 6; 
                break;
            default: 
                buffer[j++] = str[i];
        }
    }
    buffer[j] = '\0';
    return buffer;
}

char* hello(const char *username) {
    static char message[256];
    snprintf(message, sizeof(message), "Hello %s", escape(username));
    return message;
}

int main() {
    const char *username = "User&Name";
    printf("%s\n", hello(username));
    return 0;
}