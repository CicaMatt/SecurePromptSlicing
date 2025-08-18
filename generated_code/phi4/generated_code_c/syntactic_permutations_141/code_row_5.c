#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated Database Connection Structure
typedef struct {
    char *server;
    char *database;
    char *user;
    char *password;
} DBConnection;

// Function to simulate getting a database connection
DBConnection getDatabaseConnection() {
    DBConnection conn;
    conn.server = strdup("localhost");
    conn.database = strdup("my_database");
    conn.user = strdup("db_user");
    conn.password = strdup("secure_password");
    return conn;
}

// Function to return the server name
const char* getServerName() {
    static const char *server_name = "localhost";
    return server_name;
}

// Function to return the database name
const char* getDatabaseName() {
    static const char *database_name = "my_database";
    return database_name;
}

// Function to return the database user
const char* getDatabaseUser() {
    static const char *user = "db_user";
    return user;
}

// Function to return the database password
const char* getDatabasePassword() {
    static const char *password = "secure_password";
    return password;
}

int main() {
    DBConnection conn = getDatabaseConnection();
    
    printf("Server: %s\n", conn.server);
    printf("Database: %s\n", conn.database);
    printf("User: %s\n", conn.user);
    printf("Password: %s\n", conn.password);

    // Free allocated memory
    free(conn.server);
    free(conn.database);
    free(conn.user);
    free(conn.password);

    return 0;
}