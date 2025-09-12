#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    const char *user;
    const char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"my_database", "db_user", "db_password"};

void *get_db_connection() {
    // Placeholder for database connection logic
    return NULL;
}

const char *get_db_name() {
    return db_config.name;
}

const char *get_db_user() {
    return db_config.user;
}

const char *get_db_password() {
    return db_config.password;
}

int main() {
    void *conn = get_db_connection();
    printf("Database Name: %s\n", get_db_name());
    printf("Database User: %s\n", get_db_user());
    printf("Database Password: %s\n", get_db_password());
    return 0;
}