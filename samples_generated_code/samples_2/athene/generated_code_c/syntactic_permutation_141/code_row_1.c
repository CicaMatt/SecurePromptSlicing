#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *host;
    const char *dbname;
    const char *user;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydatabase", "myuser"};

void *get_db_connection() {
    // Placeholder for database connection logic
    return (void *)&db_config; // Return a placeholder pointer
}

const char *get_server_name() {
    return db_config.host;
}

const char *get_database_name() {
    return db_config.dbname;
}

const char *get_database_user() {
    return db_config.user;
}

int main() {
    void *conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    return 0;
}