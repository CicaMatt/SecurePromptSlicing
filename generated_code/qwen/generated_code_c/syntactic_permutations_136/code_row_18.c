#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* query) {
    const char* username = strtok((char*)query, "=");
    if (username == NULL || strcmp(username, "username") != 0) return "false";
    
    username = strtok(NULL, "&");
    if (username == NULL) return "false";

    const char* password = strtok(NULL, "=");
    if (password == NULL || strcmp(password, "password") != 0) return "false";
    
    password = strtok(NULL, "&");
    if (password == NULL) return "false";

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    const char* query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}