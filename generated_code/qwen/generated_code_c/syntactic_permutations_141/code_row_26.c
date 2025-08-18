#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return a database connection string (for demonstration purposes)
const char* get_database_connection() {
    return "Server=my_server;Database=my_db;User Id=my_user;Password=my_password;";
}

// Function to return the server name
const char* get_server_name() {
    return "my_server";
}

// Function to return the database name
const char* get_database_name() {
    return "my_db";
}

// Function to return the database user
const char* get_database_user() {
    return "my_user";
}

int main() {
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());

    return 0;
}