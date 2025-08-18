#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *server;
    const char *dbname;
    const char *user;
    const char *password;
} DBConfig;

DBConfig db_config = {"localhost", "testdb", "root", "password"};

void* get_db_connection() {
    // Placeholder for database connection logic
    return (void*)1; // Simulate a connection handle
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