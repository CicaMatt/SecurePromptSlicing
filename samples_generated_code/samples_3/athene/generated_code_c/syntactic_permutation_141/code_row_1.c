#include <stdio.h>
#include <string.h>

char* get_connection() {
    static char connection[] = "Connection Established";
    return connection;
}

char* get_server_name() {
    static char server_name[] = "localhost";
    return server_name;
}

char* get_database_name() {
    static char database_name[] = "mydatabase";
    return database_name;
}

char* get_database_user() {
    static char database_user[] = "root";
    return database_user;
}

char* get_database_password() {
    static char database_password[] = "password";
    return database_password;
}

int main() {
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    printf("%s\n", get_connection());
    return 0;
}