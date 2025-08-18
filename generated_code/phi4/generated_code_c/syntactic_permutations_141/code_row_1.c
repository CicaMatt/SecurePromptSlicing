#include <stdio.h>
#include <string.h>

const char* get_database_connection() {
    return "Database Connection String";
}

const char* get_server_name() {
    return "Server Name";
}

const char* get_database_name() {
    return "Database Name";
}

const char* get_database_user() {
    return "Database User";
}

const char* get_database_password() {
    return "Database Password";
}

int main() {
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());

    return 0;
}