#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return a database connection (mock implementation)
void* getDatabaseConnection() {
    // In a real scenario, this would involve actual database connection logic
    return malloc(sizeof(void*));
}

// Function to return the server name
const char* getServerName() {
    return "localhost";
}

// Function to return the database name
const char* getDatabaseName() {
    return "example_db";
}

// Function to return the database user
const char* getDatabaseUser() {
    return "user";
}

// Function to return the database password
const char* getDatabasePassword() {
    return "password";
}

int main() {
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    // Simulate getting a database connection
    void* dbConnection = getDatabaseConnection();
    if (dbConnection != NULL) {
        printf("Successfully connected to the database.\n");
        free(dbConnection);
    } else {
        printf("Failed to connect to the database.\n");
    }

    return 0;
}