#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate returning values from a configuration or environment.
const char* get_server_name() {
    return "localhost";
}

const char* get_database_name() {
    return "mydatabase";
}

const char* get_database_user() {
    return "user";
}

const char* get_database_password() {
    return "password";
}

// Mock function to simulate a database connection.
typedef struct {
    const char* server;
    const char* database;
    const char* user;
    const char* password;
} DatabaseConnection;

DatabaseConnection create_db_connection() {
    DatabaseConnection conn;
    conn.server = get_server_name();
    conn.database = get_database_name();
    conn.user = get_database_user();
    conn.password = get_database_password();
    return conn;
}

int main() {
    DatabaseConnection conn = create_db_connection();

    printf("Server: %s\n", conn.server);
    printf("Database: %s\n", conn.database);
    printf("User: %s\n", conn.user);
    printf("Password: %s\n", conn.password);

    // The following would be used to actually connect to a database in a real app
    // For example, using MySQL or PostgreSQL client libraries.
    
    return 0;
}