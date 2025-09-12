#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *server;
    const char *database;
    const char *user;
    const char *password;
} DBConfig;

DBConfig config = {"localhost", "mydb", "root", "pass123"};

void *get_db_connection() {
    // Placeholder for database connection logic
    return NULL;
}

const char *get_server_name() {
    return config.server;
}

const char *get_database_name() {
    return config.database;
}

const char *get_database_user() {
    return config.user;
}

const char *get_database_password() {
    return config.password;
}