#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    char *dbname;
    // Simulate a database connection handle
    void *conn;
} DatabaseConnection;

DatabaseConnection* create_db_connection() {
    DatabaseConnection *db = (DatabaseConnection *)malloc(sizeof(DatabaseConnection));
    db->host = "localhost";
    db->dbname = "testdb";
    db->conn = (void*)1; // Dummy connection handle
    return db;
}

char* get_server_name() {
    static char server_name[] = "localhost";
    return server_name;
}

char* get_database_name() {
    static char database_name[] = "testdb";
    return database_name;
}

// Placeholder for the incomplete function definition
void undefined_function() {}

int main() {
    DatabaseConnection *db_conn = create_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    // Use db_conn as needed...
    free(db_conn);
    return 0;
}