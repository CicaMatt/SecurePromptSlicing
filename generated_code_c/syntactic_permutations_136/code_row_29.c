#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* check_mod(const char* username, const char* password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123")) {
        return 'true';
    } else {
        return 'false';
    }
}

int main() {
    char* username = getenv("QUERY_STRING");
    char* password = getenv("HTTP_PASSWORD");
    
    if (check_mod(username, password) == 'true') {
        printf("Hello admin!");
    } else {
        printf("Access denied!");
    }
}