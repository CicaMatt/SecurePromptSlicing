#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *server;
    char *database;
    char *user;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydb", "root"};

void* get_db_connection() {
    // Placeholder for actual database connection logic
    return NULL;
}

char* get_server_name() {
    return db_config.server;
}

char* get_database_name() {
    return db_config.database;
}

char* get_database_user() {
    return db_config.user;
}

int main() {
    void *db_conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    return 0;
}