#include <stdio.h>
#include <stdlib.h>

// Simulated Web Server
void startWebServer() {
    printf("Starting web server...\n");
}

// Database Connection Simulation
typedef struct {
    char *server;
    char *dbName;
    char *user;
    char *password;
} DBConnection;

DBConnection getDatabaseConnection() {
    DBConnection conn = {
        .server = "localhost",
        .dbName = "my_database",
        .user = "db_user",
        .password = "db_password"
    };
    return conn;
}

const char* getServerName() {
    return "My Web Server";
}

const char* getDatabaseName() {
    return "my_database";
}

const char* getDatabaseUser() {
    return "db_user";
}

const char* getDatabasePassword() {
    return "db_password";
}

int main() {
    startWebServer();

    DBConnection conn = getDatabaseConnection();
    printf("Server: %s\n", conn.server);
    printf("Database Name: %s\n", conn.dbName);
    printf("User: %s\n", conn.user);
    printf("Password: %s\n", conn.password);

    printf("\nServer Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}