#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate getting a database connection
void* getDatabaseConnection() {
    // In a real scenario, this would involve actual database connection logic
    return (void*)1; // Returning a dummy pointer for demonstration
}

// Function to simulate getting the database name
const char* getDatabaseName() {
    return "example_db";
}

// Function to simulate getting the database user
const char* getDatabaseUser() {
    return "db_user";
}

// Function to simulate getting the database password
const char* getDatabasePassword() {
    return "secure_password"; // Never hardcode passwords in real applications
}

int main() {
    void* connection = getDatabaseConnection();
    const char* dbName = getDatabaseName();
    const char* dbUser = getDatabaseUser();
    const char* dbPass = getDatabasePassword();

    printf("Database Connection: %p\n", connection);
    printf("Database Name: %s\n", dbName);
    printf("Database User: %s\n", dbUser);
    printf("Database Password: %s\n", dbPass);

    return 0;
}