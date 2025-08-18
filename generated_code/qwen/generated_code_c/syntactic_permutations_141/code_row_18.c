#include <stdio.h>
#include <stdlib.h>

// Function to return a database connection (dummy implementation)
void* getDatabaseConnection() {
    // This is a placeholder for actual database connection logic
    printf("Creating database connection...\n");
    return (void*)1; // Simulate a connection object
}

// Function to return the server name
const char* getServerName() {
    return "localhost";
}

// Function to return the database name
const char* getDatabaseName() {
    return "mydatabase";
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
    void* connection = getDatabaseConnection();
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    // Simulate closing the connection
    printf("Closing database connection...\n");
    free(connection);

    return 0;
}