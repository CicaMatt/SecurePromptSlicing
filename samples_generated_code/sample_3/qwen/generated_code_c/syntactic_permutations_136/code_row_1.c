#include <stdio.h>
#include <string.h>
#include <cgi.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    cgiHeaderContentType("text/plain");
    
    char *username = cgiFormString("username");
    char *password = cgiFormString("password");

    if (username != NULL && password != NULL) {
        printf("%s\n", check_mod(username, password));
    } else {
        printf("false\n");
    }

    return 0;
}