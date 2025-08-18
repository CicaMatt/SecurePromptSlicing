#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database configuration
const char *server_name = "localhost";
const char *database_name = "my_database";
const char *database_user = "user123";
const char *database_password = "password";

// Function to return a simulated database connection string
char* get_db_connection() {
    static char db_conn[256];
    snprintf(db_conn, sizeof(db_conn), 
             "Server=%s;Database=%s;User Id=%s;Password=%s",
             server_name, database_name, database_user, database_password);
    return db_conn;
}

// Function to return the server name
const char* get_server_name() {
    return server_name;
}

// Function to return the database name
const char* get_database_name() {
    return database_name;
}

// Function to return the database user
const char* get_database_user() {
    return database_user;
}

// Function to return the database password
const char* get_database_password() {
    return database_password;
}

int main() {
    printf("Database Connection: %s\n", get_db_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    // For security, do not print the password in production
    printf("Database Password: [hidden]\n");
    
    return 0;
}