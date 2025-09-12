#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate getting a database connection (returns a dummy string)
const char* get_database_connection() {
    return "Database Connection Established";
}

// Function to return the server name
const char* get_server_name() {
    return "localhost";
}

// Function to return the database name
const char* get_database_name() {
    return "example_db";
}

// Function to return the database user
const char* get_database_user() {
    return "admin";
}

int main() {
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("%s\n", get_database_connection());
    return 0;
}