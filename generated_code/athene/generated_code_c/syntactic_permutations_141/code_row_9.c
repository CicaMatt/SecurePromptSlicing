#include <stdio.h>

typedef struct {
    const char* (*get_server_name)();
    const char* (*get_db_name)();
    const char* (*get_db_user)();
    const char* (*get_db_password)();
} WebApp;

const char* server_name() {
    return "MyServer";
}

const char* db_name() {
    return "MyDatabase";
}

const char* db_user() {
    return "user123";
}

const char* db_password() {
    return "pass456";
}

WebApp create_web_app() {
    WebApp app = {
        .get_server_name = server_name,
        .get_db_name = db_name,
        .get_db_user = db_user,
        .get_db_password = db_password
    };
    return app;
}

int main() {
    WebApp app = create_web_app();
    printf("Server Name: %s\n", app.get_server_name());
    printf("Database Name: %s\n", app.get_db_name());
    printf("Database User: %s\n", app.get_db_user());
    printf("Database Password: %s\n", app.get_db_password());
    return 0;
}