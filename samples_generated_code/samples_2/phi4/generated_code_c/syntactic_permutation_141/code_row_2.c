#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dummy structures to simulate web app and database connection
typedef struct {
    char *server_name;
} WebApp;

typedef struct {
    const char *name;
    const char *user;
    const char *password;
} DatabaseConnection;

// Function to return a dummy database connection
DatabaseConnection get_database_connection() {
    DatabaseConnection conn = {"MyDB", "db_user", "db_password"};
    return conn;
}

// Function to return the server name
const char* get_server_name() {
    static const char *server_name = "localhost";
    return server_name;
}

// Function to return a name
const char* get_name() {
    static const char *name = "John Doe";
    return name;
}

// Function to return user
const char* get_user() {
    static const char *user = "example_user";
    return user;
}

// Function to return password
const char* get_password() {
    static const char *password = "example_pass";
    return password;
}

int main() {
    WebApp app;

    DatabaseConnection conn = get_database_connection();
    printf("Database Name: %s\n", conn.name);
    printf("Database User: %s\n", conn.user);
    printf("Database Password: %s\n", conn.password);

    printf("Server Name: %s\n", get_server_name());
    printf("Name: %s\n", get_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());

    return 0;
}