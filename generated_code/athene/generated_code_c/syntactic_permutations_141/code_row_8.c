#include <stdio.h>
#include <string.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "mydatabase"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

char* get_server_name() {
    return SERVER_NAME;
}

char* get_database_name() {
    return DATABASE_NAME;
}

char* get_database_user() {
    return DATABASE_USER;
}

char* get_database_password() {
    return DATABASE_PASSWORD;
}

void* create_db_connection() {
    // Placeholder for database connection logic
    // In a real application, this would establish and return an actual DB connection
    printf("Creating database connection...\n");
    return NULL;
}

int main() {
    void *db_conn = create_db_connection();
    if (db_conn) {
        printf("Server Name: %s\n", get_server_name());
        printf("Database Name: %s\n", get_database_name());
        printf("Database User: %s\n", get_database_user());
        printf("Database Password: %s\n", get_database_password());
    } else {
        printf("Failed to create database connection.\n");
    }
    return 0;
}