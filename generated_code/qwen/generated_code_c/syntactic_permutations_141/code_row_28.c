#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return a database connection string (simplified for example)
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

int main() {
    printf("Database Connection: %s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());

    return 0;
}