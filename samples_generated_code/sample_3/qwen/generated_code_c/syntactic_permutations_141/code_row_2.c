#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking database connection and server functionalities

typedef struct {
    char *connection_string;
} DatabaseConnection;

DatabaseConnection* get_database_connection() {
    DatabaseConnection *conn = malloc(sizeof(DatabaseConnection));
    conn->connection_string = strdup("Server=myServerAddress;Database=myDataBase;User Id=myUsername;Password=myPassword;");
    return conn;
}

char* get_server_name() {
    return strdup("MyServerName");
}

void free_database_connection(DatabaseConnection *conn) {
    if (conn != NULL) {
        free(conn->connection_string);
        free(conn);
    }
}

int main() {
    DatabaseConnection *db_conn = get_database_connection();
    char *server_name = get_server_name();

    printf("Database Connection String: %s\n", db_conn->connection_string);
    printf("Server Name: %s\n", server_name);

    free_database_connection(db_conn);
    free(server_name);

    return 0;
}