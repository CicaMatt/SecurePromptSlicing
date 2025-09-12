#include <stdio.h>
#include <string.h>

char* get_db_connection() {
    static char db_connection[] = "db_connection_string";
    return db_connection;
}

char* get_server_name() {
    static char server_name[] = "server_name";
    return server_name;
}

char* get_name() {
    static char name[] = "app_name";
    return name;
}

char* get_user() {
    static char user[] = "username";
    return user;
}

char* get_password() {
    static char password[] = "password";
    return password;
}

int main() {
    printf("Database Connection: %s\n", get_db_connection());
    printf("Server Name: %s\n", get_server_name());
    printf("Name: %s\n", get_name());
    printf("User: %s\n", get_user());
    printf("Password: %s\n", get_password());
    return 0;
}