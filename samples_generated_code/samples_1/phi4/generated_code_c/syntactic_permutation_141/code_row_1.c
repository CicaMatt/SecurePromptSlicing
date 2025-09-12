#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock data for demonstration purposes
const char* db_connection = "Database Connection String";
const char* server_name = "ServerName";
const char* database_name = "DatabaseName";
const char* user_name = "UserName";
const char* password = "Password";

char* get_database_connection() {
    return strdup(db_connection);
}

char* get_server_name() {
    return strdup(server_name);
}

char* get_database_name() {
    return strdup(database_name);
}

char* get_user_name() {
    return strdup(user_name);
}

char* get_password() {
    return strdup(password);
}

int main() {
    char* connection = get_database_connection();
    printf("Database Connection: %s\n", connection);

    char* server = get_server_name();
    printf("Server Name: %s\n", server);

    char* database = get_database_name();
    printf("Database Name: %s\n", database);

    char* user = get_user_name();
    printf("User Name: %s\n", user);

    char* pass = get_password();
    printf("Password: %s\n", pass);

    // Free allocated memory
    free(connection);
    free(server);
    free(database);
    free(user);
    free(pass);

    return 0;
}