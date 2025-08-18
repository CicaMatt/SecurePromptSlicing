#include <stdio.h>
#include <stdlib.h>

// Mock definitions for demonstration purposes
typedef struct {
    const char* host;
    int port;
} Server;

typedef struct {
    const char* name;
} Database;

typedef struct {
    const char* username;
    const char* password;
} UserCredentials;

typedef struct {
    Server server;
    Database database;
    UserCredentials user;
} DBConnection;

// Function to return a mock database connection
DBConnection getDatabaseConnection() {
    DBConnection conn = {
        .server = { "localhost", 5432 },
        .database = { "my_database" },
        .user = { "db_user", "db_password" }
    };
    return conn;
}

// Function to return the server name
const char* getServerName() {
    static const char* server_name = "MyWebAppServer";
    return server_name;
}

// Function to return the database name
const char* getDatabaseName() {
    static const char* database_name = "my_database";
    return database_name;
}

// Function to return the database user
const char* getDatabaseUser() {
    static const char* user = "db_user";
    return user;
}

// Function to return the database password
const char* getDatabasePassword() {
    static const char* password = "db_password";
    return password;
}

int main() {
    DBConnection conn = getDatabaseConnection();
    printf("Server: %s, Port: %d\n", conn.server.host, conn.server.port);
    printf("Database: %s\n", conn.database.name);
    printf("User: %s\n", conn.user.username);

    printf("\nServer Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}