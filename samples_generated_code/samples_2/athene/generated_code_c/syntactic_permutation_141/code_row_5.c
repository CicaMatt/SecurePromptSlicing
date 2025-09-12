#include <stdio.h>
#include <string.h>

char* get_server_name() {
    static char server_name[] = "localhost";
    return server_name;
}

char* get_database_name() {
    static char database_name[] = "mydatabase";
    return database_name;
}

char* get_database_user() {
    static char database_user[] = "user123";
    return database_user;
}

void* get_db_connection() {
    // Placeholder for a database connection
    // In a real application, this would connect to the database and return a handle.
    printf("Connecting to %s@%s/%s\n", get_database_user(), get_server_name(), get_database_name());
    return NULL; // Replace with actual connection logic
}

int main() {
    void* db_conn = get_db_connection();
    if (db_conn != NULL) {
        printf("Database connection successful.\n");
    } else {
        printf("Failed to connect to the database.\n");
    }
    return 0;
}