#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated environment for demonstration purposes.
typedef struct {
    char *name;
    char *user;
    char *password;
} DatabaseConnection;

DatabaseConnection get_database_connection() {
    return (DatabaseConnection){
        .name = "example_db",
        .user = "db_user",
        .password = "secure_password"
    };
}

const char* get_name() {
    return "My Web App";
}

const char* get_database_name(DatabaseConnection conn) {
    return conn.name;
}

const char* get_database_user(DatabaseConnection conn) {
    return conn.user;
}

const char* get_database_password(DatabaseConnection conn) {
    return conn.password;
}

int main() {
    printf("Web App Name: %s\n", get_name());

    DatabaseConnection db_conn = get_database_connection();
    
    printf("Database Name: %s\n", get_database_name(db_conn));
    printf("Database User: %s\n", get_database_user(db_conn));
    printf("Database Password: %s\n", get_database_password(db_conn));

    return 0;
}