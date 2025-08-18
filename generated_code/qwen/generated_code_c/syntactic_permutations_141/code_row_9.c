#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* (*get_server_name)();
    const char* (*get_database_name)();
    const char* (*get_database_user)();
    const char* (*get_database_password)();
} WebApp;

const char* get_server_name() {
    return "localhost";
}

const char* get_database_name() {
    return "example_db";
}

const char* get_database_user() {
    return "admin";
}

const char* get_database_password() {
    return "password123";
}

WebApp* create_web_app() {
    WebApp* app = (WebApp*)malloc(sizeof(WebApp));
    if (!app) return NULL;

    app->get_server_name = get_server_name;
    app->get_database_name = get_database_name;
    app->get_database_user = get_database_user;
    app->get_database_password = get_database_password;

    return app;
}

int main() {
    WebApp* app = create_web_app();
    if (!app) {
        fprintf(stderr, "Failed to create web app\n");
        return EXIT_FAILURE;
    }

    printf("Server Name: %s\n", app->get_server_name());
    printf("Database Name: %s\n", app->get_database_name());
    printf("Database User: %s\n", app->get_database_user());
    printf("Database Password: %s\n", app->get_database_password());

    free(app);
    return EXIT_SUCCESS;
}