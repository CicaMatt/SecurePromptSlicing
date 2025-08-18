#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock definitions for demonstration purposes
#define SERVER_NAME "localhost"
#define DATABASE_NAME "mydatabase"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

typedef struct {
    char server[50];
    char database[50];
    char user[50];
    char password[50];
} DBConnection;

DBConnection getDatabaseConnection() {
    DBConnection conn;
    strcpy(conn.server, SERVER_NAME);
    strcpy(conn.database, DATABASE_NAME);
    strcpy(conn.user, DATABASE_USER);
    strcpy(conn.password, DATABASE_PASSWORD);
    return conn;
}

const char* getServerName() {
    static const char server[] = SERVER_NAME;
    return server;
}

const char* getDatabaseName() {
    static const char database[] = DATABASE_NAME;
    return database;
}

const char* getDatabaseUser() {
    static const char user[] = DATABASE_USER;
    return user;
}

const char* getDatabasePassword() {
    static const char password[] = DATABASE_PASSWORD;
    return password;
}

int main() {
    // Example usage
    DBConnection conn = getDatabaseConnection();
    printf("Server: %s\n", getServerName());
    printf("Database: %s\n", getDatabaseName());
    printf("User: %s\n", getDatabaseUser());
    printf("Password: %s\n", getDatabasePassword());

    return 0;
}