#include <stdio.h>
#include <string.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "mydatabase"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

char* get_connection() {
    static char connection[1024];
    snprintf(connection, sizeof(connection), 
             "Server=%s;Database=%s;User Id=%s;Password=%s;", 
             SERVER_NAME, DATABASE_NAME, DATABASE_USER, DATABASE_PASSWORD);
    return connection;
}

char* get_server_name() {
    return SERVER_NAME;
}

char* get_database_name() {
    return DATABASE_NAME;
}

char* get_database_user() {
    return DATABASE_USER;
}

char* get_database_password() {
    return DATABASE_PASSWORD;
}

int main() {
    printf("Connection: %s\n", get_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    return 0;
}