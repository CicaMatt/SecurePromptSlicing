#include <stdio.h>
#include <string.h>

typedef struct {
    char *server;
    char *dbname;
    char *user;
    char *password;
} DBConfig;

DBConfig db_config = {"localhost", "mydatabase", "root", "password"};

void* get_db_connection() {
    // Placeholder for actual database connection logic
    return NULL;
}

const char* get_server_name() {
    return db_config.server;
}

const char* get_database_name() {
    return db_config.dbname;
}

const char* get_database_user() {
    return db_config.user;
}

const char* get_database_password() {
    return db_config.password;
}