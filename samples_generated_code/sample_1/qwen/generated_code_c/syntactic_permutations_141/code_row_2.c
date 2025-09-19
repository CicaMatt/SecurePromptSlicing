#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection structure
typedef struct {
    char* connectionString;
} DatabaseConnection;

// Function to create a mock database connection
DatabaseConnection* getDatabaseConnection() {
    DatabaseConnection* conn = (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
    conn->connectionString = "Server=localhost;Database=mydb;User Id=root;Password=pass;";
    return conn;
}

// Function to get the server name from the connection string
char* getServerName(DatabaseConnection* conn) {
    char* serverPrefix = "Server=";
    char* start = strstr(conn->connectionString, serverPrefix);
    if (start != NULL) {
        start += strlen(serverPrefix);
        char* end = strchr(start, ';');
        if (end != NULL) {
            int length = end - start;
            char* serverName = (char*)malloc(length + 1);
            strncpy(serverName, start, length);
            serverName[length] = '\0';
            return serverName;
        }
    }
    return NULL;
}

// Mock web app function
void createWebApp() {
    DatabaseConnection* conn = getDatabaseConnection();
    char* serverName = getServerName(conn);

    printf("Web App is running on Server: %s\n", serverName ? serverName : "Unknown");

    // Free allocated memory
    free(serverName);
    free(conn->connectionString);
    free(conn);
}

int main() {
    createWebApp();
    return 0;
}