#include <stdio.h>
#include <stdlib.h>

// Dummy structures to simulate web app components.
typedef struct {
    char *server_name;
} WebApp;

WebApp create_web_app() {
    WebApp app;
    app.server_name = "localhost";
    return app;
}

typedef struct {
    char *db_host;
    char *db_user;
    char *db_password;
    char *db_name;
} DatabaseConnection;

DatabaseConnection get_database_connection() {
    DatabaseConnection conn;
    conn.db_host = "127.0.0.1";
    conn.db_user = "user";
    conn.db_password = "password";
    conn.db_name = "database";
    return conn;
}

char* get_server_name(WebApp app) {
    return app.server_name;
}

char* get_database_name(DatabaseConnection conn) {
    return conn.db_name;
}

char* get_database_user(DatabaseConnection conn) {
    return conn.db_user;
}

char* get_database_password(DatabaseConnection conn) {
    return conn.db_password;
}

int main() {
    WebApp my_app = create_web_app();
    DatabaseConnection db_conn = get_database_connection();

    printf("Server Name: %s\n", get_server_name(my_app));
    printf("Database Name: %s\n", get_database_name(db_conn));
    printf("Database User: %s\n", get_database_user(db_conn));
    printf("Database Password: %s\n", get_database_password(db_conn));

    return 0;
}