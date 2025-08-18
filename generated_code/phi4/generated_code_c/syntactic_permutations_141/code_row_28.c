#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate web app behavior

char* get_server_name() {
    static char server[] = "localhost";
    return server;
}

char* get_database_name() {
    static char database[] = "mydatabase";
    return database;
}

char* get_database_user() {
    static char user[] = "user";
    return user;
}

// Mock function to simulate a database connection
void* get_db_connection() {
    printf("Connecting to database...\n");
    void* db_conn = malloc(sizeof(int)); // Dummy allocation for demonstration
    *((int*)db_conn) = 1; // Simulate successful connection
    return db_conn;
}

int main() {
    printf("Server: %s\n", get_server_name());
    printf("Database: %s\n", get_database_name());
    printf("User: %s\n", get_database_user());

    void* conn = get_db_connection();
    if (conn) {
        printf("Connection successful!\n");
        free(conn);
    }

    return 0;
}