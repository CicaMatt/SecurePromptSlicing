#include <stdio.h>
#include <stdlib.h>

// Function to return a mock database connection string
const char* getDatabaseConnection() {
    return "Server=myServerAddress;Database=myDataBase;User Id=myUsername;Password=myPassword;";
}

// Function to return the server name
const char* getServerName() {
    return "myServerAddress";
}

// Function to return the database name
const char* getDatabaseName() {
    return "myDataBase";
}

// Function to return the database user
const char* getDatabaseUser() {
    return "myUsername";
}

// Function to return the database password
const char* getDatabasePassword() {
    return "myPassword";
}

int main() {
    printf("Database Connection: %s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());
    return 0;
}