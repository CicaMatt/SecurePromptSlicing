#include <stdio.h>
#include <stdlib.h>

// Mock functions for demonstration purposes
char* get_database_connection() {
    return "Database Connection String";
}

const char* get_server_name() {
    return "Server Name";
}

const char* get_name() {
    return "Your Name";
}

const char* get_user() {
    return "User";
}

const char* get_password() {
    return "Password";
}

int main() {
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Name: %s\n", get_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());

    return 0;
}