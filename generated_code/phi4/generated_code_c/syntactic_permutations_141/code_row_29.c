#include <stdio.h>
#include <stdlib.h>

// Define constants for configuration (in practice, load these from secure storage)
#define SERVER_NAME "localhost"
#define DATABASE_NAME "my_database"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

typedef struct {
    // Simulating a database connection structure
    char *server_name;
    char *database_name;
    char *user;
    char *password;
} DatabaseConnection;

DatabaseConnection get_database_connection() {
    DatabaseConnection conn = {SERVER_NAME, DATABASE_NAME, DATABASE_USER, DATABASE_PASSWORD};
    return conn;
}

const char* get_server_name() {
    return SERVER_NAME;
}

const char* get_database_name() {
    return DATABASE_NAME;
}

const char* get_database_user() {
    return DATABASE_USER;
}

const char* get_database_password() {
    return DATABASE_PASSWORD;
}

int main() {
    DatabaseConnection conn = get_database_connection();
    
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());

    // Simulated web app functionality
    printf("Welcome to the Web App!\n");

    return 0;
}