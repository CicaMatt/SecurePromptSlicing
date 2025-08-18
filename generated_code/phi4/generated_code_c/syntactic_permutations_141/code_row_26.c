#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate behavior since C does not natively support web apps or databases

void start_web_app() {
    printf("Web app started.\n");
}

char* get_database_connection() {
    return "DatabaseConnection";
}

const char* get_server_name() {
    static const char server[] = "ServerName";
    return server;
}

const char* get_database_name() {
    static const char database[] = "DatabaseName";
    return database;
}

const char* get_database_user() {
    static const char user[] = "DatabaseUser";
    return user;
}

int main() {
    start_web_app();
    
    printf("Database Connection: %s\n", get_database_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());

    return 0;
}