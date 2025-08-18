#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* host;
    char* name;
    char* user;
    char* password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydatabase", "user123", "pass456"};

void *get_db_connection() {
    // Placeholder for actual database connection logic
    return NULL;
}

char* get_db_name() {
    return db_config.name;
}

char* get_db_user() {
    return db_config.user;
}

char* get_db_password() {
    return db_config.password;
}

int main() {
    void *conn = get_db_connection();
    char *dbname = get_db_name();
    char *dbuser = get_db_user();
    char *dbpassword = get_db_password();

    printf("Database Name: %s\n", dbname);
    printf("Database User: %s\n", dbuser);
    printf("Database Password: %s\n", dbpassword);

    return 0;
}