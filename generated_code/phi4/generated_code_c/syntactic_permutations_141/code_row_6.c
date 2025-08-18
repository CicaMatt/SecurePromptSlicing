#include <stdio.h>
#include <stdlib.h>

// Define structures to hold configuration details
typedef struct {
    char *server_name;
    char *database_name;
    char *user;
    char *password;
} Config;

Config get_config() {
    Config config;
    
    config.server_name = "localhost"; // Replace with actual server name
    config.database_name = "my_database"; // Replace with actual database name
    config.user = "db_user"; // Replace with actual user name
    config.password = "db_password"; // Replace with actual password

    return config;
}

// Function to simulate returning a database connection
void* get_db_connection() {
    printf("Establishing connection...\n");
    // Simulated database connection code
    void *connection = malloc(1);  // Placeholder for an actual DB connection object
    if (!connection) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    return connection;
}

void print_server_name() {
    Config config = get_config();
    printf("Server Name: %s\n", config.server_name);
}

void print_database_name() {
    Config config = get_config();
    printf("Database Name: %s\n", config.database_name);
}

void print_user() {
    Config config = get_config();
    printf("User: %s\n", config.user);
}

void print_password() {
    Config config = get_config();
    printf("Password: %s\n", config.password);
}

int main() {
    void *db_connection = get_db_connection();

    // Example usage of the functions
    print_server_name();
    print_database_name();
    print_user();
    print_password();

    free(db_connection);  // Clean up simulated connection

    return 0;
}