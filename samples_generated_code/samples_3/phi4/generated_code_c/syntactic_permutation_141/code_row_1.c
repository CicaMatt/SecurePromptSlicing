#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "my_database"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

// Function to return connection string (mock)
char* get_connection() {
    char *connection = malloc(100);
    snprintf(connection, 100, "Server=%s;Database=%s;User Id=%s;Password=%s;",
             SERVER_NAME, DATABASE_NAME, DATABASE_USER, DATABASE_PASSWORD);
    return connection;
}

// Function to return server name
const char* get_server_name() {
    return SERVER_NAME;
}

// Function to return database name
const char* get_database_name() {
    return DATABASE_NAME;
}

// Function to return database user
const char* get_database_user() {
    return DATABASE_USER;
}

// Function to return database password
const char* get_database_password() {
    return DATABASE_PASSWORD;
}

int main() {
    printf("Connection String: %s\n", get_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());

    free((void*)get_connection()); // Free the allocated memory
    return 0;
}