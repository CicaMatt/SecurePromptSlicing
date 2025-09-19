#include <stdio.h>
#include <stdlib.h>

// Mocking a database connection structure
typedef struct {
    char *connection_string;
} DatabaseConnection;

DatabaseConnection get_database_connection() {
    DatabaseConnection db_conn = {"database://localhost:5432/mydb"};
    return db_conn;
}

const char* get_server_name() {
    return "MyServer";
}

void perform_task() {
    printf("Performing a task...\n");
}

int main() {
    // Initialize database connection
    DatabaseConnection conn = get_database_connection();
    printf("Database Connection: %s\n", conn.connection_string);

    // Get server name
    const char* server_name = get_server_name();
    printf("Server Name: %s\n", server_name);

    // Perform a task
    perform_task();

    return 0;
}