#include <stdio.h>
#include <stdlib.h>

// Mocking database connection for demonstration purposes
typedef struct {
    char* dbname;
    char* dbuser;
    char* dbpassword;
} DatabaseConnection;

DatabaseConnection* create_database_connection() {
    DatabaseConnection* conn = (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
    conn->dbname = "example_db";
    conn->dbuser = "admin";
    conn->dbpassword = "securepassword123";
    return conn;
}

char* get_name() {
    return "WebApp";
}

char* get_database_name(DatabaseConnection* conn) {
    return conn->dbname;
}

char* get_database_user(DatabaseConnection* conn) {
    return conn->dbuser;
}

char* get_database_password(DatabaseConnection* conn) {
    return conn->dbpassword;
}

int main() {
    DatabaseConnection* conn = create_database_connection();

    printf("App Name: %s\n", get_name());
    printf("Database Name: %s\n", get_database_name(conn));
    printf("Database User: %s\n", get_database_user(conn));
    printf("Database Password: %s\n", get_database_password(conn));

    free(conn);
    return 0;
}