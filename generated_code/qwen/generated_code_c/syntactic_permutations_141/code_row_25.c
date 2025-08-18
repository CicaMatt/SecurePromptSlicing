#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate getting a database connection
const char* getDatabaseConnection() {
    return "Database Connection";
}

// Function to return the server name
const char* getServerName() {
    return "localhost";
}

// Function to return the name
const char* getName() {
    return "WebAppUser";
}

// Function to return the user
const char* getUser() {
    return "user123";
}

// Function to return the password
const char* getPassword() {
    return "password123";
}

int main() {
    printf("Database Connection: %s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Name: %s\n", getName());
    printf("User: %s\n", getUser());
    printf("Password: %s\n", getPassword());

    return 0;
}