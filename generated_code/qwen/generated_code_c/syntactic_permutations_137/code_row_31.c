#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* name, const char* password, const char* session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(name, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char* query_string) {
    char name[50], password[50], session[50];
    sscanf(query_string, "name=%49[^&]&password=%49[^&]&session=%49s", name, password, session);
    
    if (auth_mod(name, password, session)) {
        printf("Content-Type: text/plain\n\nUser is a moderator.\n");
    } else {
        printf("Content-Type: text/plain\n\nUser is not a moderator.\n");
    }
}

int main() {
    // Simulating a query string from URL
    const char* query_string = "name=admin&password=password123&session=validsession";
    
    // Output CGI header for demonstration in non-web environment
    printf("Content-Type: text/plain\n\n");
    
    check_mod(query_string);
    
    return 0;
}