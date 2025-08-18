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
    if (config != NULL) {
        free(config->name);
        free(config->user);
        free(config->password);
        free(config);
    }
}

char* get_server_name() {
    return "localhost";
}

char* get_user() {
    return "admin";
}

char* get_password() {
    return "securepassword123";
}

void *get_db_connection() {
    static DatabaseConfig *db_config = NULL;
    if (db_config == NULL) {
        db_config = create_db_config(get_server_name(), get_user(), get_password());
    }
    return db_config; // Assuming the connection is represented by this struct
}

int main() {
    void *conn = get_db_connection();
    DatabaseConfig *config = conn;
    printf("Server Name: %s\nUser: %s\nPassword: %s\n", config->name, config->user, config->password);
    free_db_config(config); // Free the memory after use
    return 0;
}