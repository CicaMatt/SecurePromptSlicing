#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *server;
    const char *dbname;
    const char *user;
    const char *password;
} DBConfig;

DBConfig config = {"localhost", "testdb", "root", "password"};

void* get_db_connection() {
    // This is a placeholder for a database connection
    return (void*)1;
}

const char* get_server_name() {
    return config.server;
}

const char* get_database_name() {
    return config.dbname;
}

const char* get_database_user() {
    return config.user;
}

const char* get_database_password() {
    return config.password;
}