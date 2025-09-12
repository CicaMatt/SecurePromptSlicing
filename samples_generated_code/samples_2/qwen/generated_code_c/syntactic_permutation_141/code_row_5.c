#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to return a database connection string
char* get_database_connection() {
    return "Server=myServerAddress;Database=myDataBase;User Id=myUsername;Password=myPassword;";
}

// Function to return the server name
char* get_server_name() {
    return "myServerAddress";
}

// Function to return the database name
char* get_database_name() {
    return "myDataBase";
}

// Function to return the database user
char* get_database_user() {
    return "myUsername";
}

int main() {
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());

    return 0;
}