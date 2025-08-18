#include <stdio.h>
#include <stdlib.h>

// Function prototypes
char* getDatabaseConnection();
const char* getServerName();
const char* getDatabaseName();
const char* getDatabaseUser();
const char* getDatabasePassword();

int main() {
    printf("Starting web app...\n");

    // Simulating the start of a web server (placeholder)
    printf("Web server started.\n");
    
    // Retrieve database connection
    char* dbConnection = getDatabaseConnection();
    printf("Database Connection: %s\n", dbConnection);

    // Retrieve server details
    const char* serverName = getServerName();
    printf("Server Name: %s\n", serverName);
    
    const char* dbName = getDatabaseName();
    printf("Database Name: %s\n", dbName);
    
    const char* dbUser = getDatabaseUser();
    printf("Database User: %s\n", dbUser);
    
    const char* dbPassword = getDatabasePassword();
    printf("Database Password: %s\n", dbPassword);

    // Clean up
    free(dbConnection);

    return 0;
}

// Function definitions

char* getDatabaseConnection() {
    // Simulate a database connection string
    char* connection = malloc(100 * sizeof(char));
    snprintf(connection, 100, "Server=%s;Database=%s;User Id=%s;Password=%s;",
             getServerName(), getDatabaseName(), getDatabaseUser(), getDatabasePassword());
    return connection;
}

const char* getServerName() {
    // Return a placeholder server name
    static const char* server = "localhost";
    return server;
}

const char* getDatabaseName() {
    // Return a placeholder database name
    static const char* dbName = "MyDatabase";
    return dbName;
}

const char* getDatabaseUser() {
    // Return a placeholder database user
    static const char* dbUser = "root";
    return dbUser;
}

const char* getDatabasePassword() {
    // Return a placeholder database password
    static const char* dbPassword = "password123";
    return dbPassword;
}