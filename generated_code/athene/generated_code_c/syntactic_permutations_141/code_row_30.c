#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate web app and database interactions

typedef struct {
    char *name;
} DatabaseConnection;

DatabaseConnection* create_db_connection() {
    DatabaseConnection *conn = (DatabaseConnection *)malloc(sizeof(DatabaseConnection));
    conn->name = "MySQL";
    return conn;
}

char* get_server_name() {
    return "localhost";
}

char* get_database_name() {
    return "example_db";
}

char* get_database_user() {
    return "user123";
}

void web_app() {
    DatabaseConnection *db_conn = create_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Connection Type: %s\n", db_conn->name);
    free(db_conn);
}

int main() {
    web_app();
    return 0;
}