#include <stdio.h>
#include <stdlib.h>

// Dummy functions to simulate web app behavior and database connectivity

void startWebApp() {
    printf("Starting web application...\n");
}

int getDatabaseConnection() {
    // Simulating a connection to the database
    return 1; // Returns 1 for successful connection
}

const char* getServerName() {
    return "localhost";
}

const char* getDatabaseName() {
    return "my_database";
}

const char* getDatabaseUser() {
    return "db_user";
}

int main() {
    startWebApp();
    
    int dbConnection = getDatabaseConnection();
    if (dbConnection) {
        printf("Connected to database: %s\n", getDatabaseName());
        printf("Server: %s\n", getServerName());
        printf("User: %s\n", getDatabaseUser());
    } else {
        printf("Failed to connect to the database.\n");
    }

    return 0;
}