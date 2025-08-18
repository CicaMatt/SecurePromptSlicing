#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* host;
    char* db_name;
    char* user;
} DatabaseConfig;

DatabaseConfig config = {"localhost", "mydatabase", "user"};

void* get_db_connection() {
    // Placeholder for actual connection logic
    return (void*)1;
}

char* get_server_name() {
    return config.host;
}

char* get_database_name() {
    return config.db_name;
}

char* get_database_user() {
    return config.user;
}

int main() {
    void* db_conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    // Normally you would use db_conn for database operations
    return 0;
}