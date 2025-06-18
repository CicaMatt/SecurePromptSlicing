#include <stdio.h>
#include <string.h>
#define MAXLEN 50

char* getUsername(char* url) {
    char* username = strtok(url, "&");
    return username;
}

char* getPassword(char* url) {
    char* password = strtok(NULL, "=");
    return password;
}

int check_mod(char* username, char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "pass123") == 0)
        return 1;
    else 
        return 0;
}

int main() {
    char url[MAXLEN];
    scanf("%s", url);

    char* username = getUsername(url);
    char* password = getPassword(url);

    if (check_mod(username, password)) {
        printf("true");
    } else {
        printf("false");
    }
    return 0;
}