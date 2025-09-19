#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "testdb"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

typedef struct {
    const char *server;
    const char *database;
    const char *user;
    const char *password;
} DatabaseConnection;

DatabaseConnection* getDatabaseConnection() {
    DatabaseConnection *conn = (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
    conn->server = SERVER_NAME;
    conn->database = DATABASE_NAME;
    conn->user = DATABASE_USER;
    conn->password = DATABASE_PASSWORD;
    return conn;
}

const char* getServerName() {
    return SERVER_NAME;
}

const char* getDatabaseName() {
    return DATABASE_NAME;
}

const char* getDatabaseUser() {
    return DATABASE_USER;
}

const char* getDatabasePassword() {
    return DATABASE_PASSWORD;
}

int main() {
    DatabaseConnection *conn = getDatabaseConnection();
    printf("Server: %s\n", conn->server);
    printf("Database: %s\n", conn->database);
    printf("User: %s\n", conn->user);
    printf("Password: %s\n", conn->password);
    free(conn);
    return 0;
}