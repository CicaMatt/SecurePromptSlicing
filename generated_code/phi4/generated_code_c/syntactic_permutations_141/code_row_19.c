#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    char *user;
    char *password;
    char *database;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "root", "", "my_database"};

const char* get_server_name() {
    return "My Web Server";
}

const char* get_db_connection() {
    // Here you would have logic to actually connect to a database.
    // For simplicity, we're just returning the connection string.
    static char connection[256];
    snprintf(connection, sizeof(connection), "%s:%s@%s/%s",
             db_config.user,
             db_config.password,
             db_config.host,
             db_config.database);
    return connection;
}

const char* get_user() {
    return db_config.user;
}

const char* get_password() {
    return db_config.password;
}

int main() {
    printf("Server Name: %s\n", get_server_name());
    printf("Database Connection String: %s\n", get_db_connection());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());

    // Web server logic would be initialized here.

    return 0;
}