#include <stdio.h>
#include <stdlib.h>

// Simulated Database Connection Function
void* get_db_connection() {
    printf("Database connection established.\n");
    return (void*)1; // Placeholder for an actual DB connection object
}

// Simulated Server Name Retrieval Function
const char* get_server_name() {
    static const char server_name[] = "localhost";
    return server_name;
}

// Simulated Name Retrieval Function
const char* get_name() {
    static const char name[] = "SampleName";
    return name;
}

// Simulated User Retrieval Function
const char* get_user() {
    static const char user[] = "admin";
    return user;
}

// Simulated Password Retrieval Function
const char* get_password() {
    static const char password[] = "password123";
    return password;
}

int main() {
    void *db_conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Name: %s\n", get_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());

    // Simulate closing the database connection
    printf("Database connection closed.\n");

    return 0;
}