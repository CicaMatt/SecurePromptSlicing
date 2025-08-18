#include <stdio.h>
#include <stdlib.h>

// Function to simulate getting a database connection (returns a dummy string)
const char* getDatabaseConnection() {
    return "Database Connection Established";
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
    return "admin";
}

// Function to return the database password
const char* getDatabasePassword() {
    return "password123"; // In a real application, never hardcode passwords
}

int main() {
    printf("Database Connection: %s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}