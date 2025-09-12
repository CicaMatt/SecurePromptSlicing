#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return "mydatabase";
}

// Function to return the database user
const char* getDatabaseUser() {
    return "user";
}

// Function to return the database password
const char* getDatabasePassword() {
    return "password"; // In a real application, avoid hardcoding passwords
}

int main() {
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());
    printf("%s\n", getDatabaseConnection());
    return 0;
}