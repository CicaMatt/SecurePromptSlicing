#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection structure for demonstration purposes
typedef struct {
    char *connection_string;
} DatabaseConnection;

// Function prototypes
DatabaseConnection get_database_connection();
const char* get_server_name();
const char* get_database_name();
const char* get_database_user();

int main() {
    // Example usage of functions
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());

    DatabaseConnection db_conn = get_database_connection();
    printf("Database Connection String: %s\n", db_conn.connection_string);

    // Clean up
    free(db_conn.connection_string);
    return 0;
}

// Function to simulate returning a database connection
DatabaseConnection get_database_connection() {
    DatabaseConnection conn;
    char *conn_str = malloc(256 * sizeof(char));
    snprintf(conn_str, 256, "Server=%s;Database=%s;User Id=%s;",
             get_server_name(), get_database_name(), get_database_user());
    conn.connection_string = conn_str;
    return conn;
}

// Function to simulate returning the server name
const char* get_server_name() {
    return "localhost";
}

// Function to simulate returning the database name
const char* get_database_name() {
    return "mydatabase";
}

// Function to simulate returning the database user
const char* get_database_user() {
    return "dbuser";
}