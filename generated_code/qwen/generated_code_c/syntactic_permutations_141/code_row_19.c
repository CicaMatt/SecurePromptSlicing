#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to simulate getting a database connection string
const char* get_database_connection() {
    return "Server=myServerAddress;Database=myDataBase;User Id=myUsername;Password=myPassword;";
}

// Function to get the server name
const char* get_server_name() {
    return "myServerAddress";
}

// Function to get the user name
const char* get_user() {
    return "myUsername";
}

// Function to get the password
const char* get_password() {
    return "myPassword";
}

int main() {
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());

    return 0;
}