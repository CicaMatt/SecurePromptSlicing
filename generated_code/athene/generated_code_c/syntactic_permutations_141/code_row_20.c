#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig* create_db_config(const char *name, const char *user, const char *password) {
    DatabaseConfig *config = (DatabaseConfig *)malloc(sizeof(DatabaseConfig));
    config->name = strdup(name);
    config->user = strdup(user);
    config->password = strdup(password);
    return config;
}

void free_db_config(DatabaseConfig *config) {
    free(config->name);
    free(config->user);
    free(config->password);
    free(config);
}

char* get_server_name() {
    return strdup("localhost");
}

DatabaseConfig* get_database_connection() {
    return create_db_config("mydb", "admin", "secret");
}

const char* get_name(DatabaseConfig *config) {
    return config->name;
}

const char* get_user(DatabaseConfig *config) {
    return config->user;
}

const char* get_password(DatabaseConfig *config) {
    return config->password;
}

int main() {
    DatabaseConfig *db = get_database_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_name(db));
    printf("User: %s\n", get_user(db));
    printf("Password: %s\n", get_password(db));
    free_db_config(db);
    return 0;
}