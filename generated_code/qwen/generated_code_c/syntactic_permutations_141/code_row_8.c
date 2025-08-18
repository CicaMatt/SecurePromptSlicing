#include <stdio.h>
#include <stdlib.h>

// Mock database connection structure
typedef struct {
    char* server;
    char* dbname;
    char* user;
    char* password;
} DBConnection;

DBConnection* createDatabaseConnection() {
    DBConnection* conn = (DBConnection*)malloc(sizeof(DBConnection));
    conn->server = getServerName();
    conn->dbname = getDatabaseName();
    conn->user = getDatabaseUser();
    conn->password = getDatabasePassword();
    return conn;
}

char* getServerName() {
    return "localhost";
}

char* getDatabaseName() {
    return "testdb";
}

char* getDatabaseUser() {
    return "admin";
}

char* getDatabasePassword() {
    return "securepassword123";
}

int main() {
    DBConnection* conn = createDatabaseConnection();
    printf("Server: %s\n", conn->server);
    printf("Database Name: %s\n", conn->dbname);
    printf("User: %s\n", conn->user);
    printf("Password: %s\n", conn->password);

    // Free allocated memory
    free(conn);
    return 0;
}