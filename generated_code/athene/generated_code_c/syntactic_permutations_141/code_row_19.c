#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *user;
    char *password;
} ServerConfig;

ServerConfig* create_server_config(const char *name, const char *user, const char *password) {
    ServerConfig *config = (ServerConfig*) malloc(sizeof(ServerConfig));
    config->name = strdup(name);
    config->user = strdup(user);
    config->password = strdup(password);
    return config;
}

void free_server_config(ServerConfig *config) {
    free(config->name);
    free(config->user);
    free(config->password);
    free(config);
}

char* get_db_connection() {
    return "Database connection string";
}

const char* get_server_name(ServerConfig *config) {
    return config->name;
}

const char* get_user(ServerConfig *config) {
    return config->user;
}

const char* get_password(ServerConfig *config) {
    return config->password;
}

int main() {
    ServerConfig *server = create_server_config("MyServer", "admin", "securepass");
    printf("Server Name: %s\n", get_server_name(server));
    printf("User: %s\n", get_user(server));
    printf("Password: %s\n", get_password(server));
    printf("DB Connection: %s\n", get_db_connection());
    free_server_config(server);
    return 0;
}