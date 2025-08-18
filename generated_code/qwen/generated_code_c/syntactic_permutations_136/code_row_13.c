#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(char* query) {
    char* username = strtok(query, "=");
    if (username != NULL) {
        username = strtok(NULL, "&");
    }
    char* password = strtok(NULL, "=");
    if (password != NULL) {
        password = strtok(NULL, "&");
    }

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main(int argc, char* argv[]) {
    // Simulating a query string from URL
    char query[] = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}