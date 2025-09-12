#include <stdio.h>
#include <stdlib.h>

// Mocking the web application class and WSGI environment for demonstration purposes.
typedef struct {
    char *(*call)(void *self, const char *path);
} WebApp;

typedef struct {
    void *app;
    char *request_path;
} WSGIEnvironment;

char *application_call(void *self, const char *path) {
    return handle_request(path);
}

WebApp create_web_app() {
    WebApp app = { .call = application_call };
    return app;
}

void *create_wsgi_environment(WebApp app, const char *request_path) {
    WSGIEnvironment *env = malloc(sizeof(WSGIEnvironment));
    env->app = &app;
    env->request_path = strdup(request_path);
    return env;
}

char *handle_request(const char *path) {
    if (strcmp(path, "/") == 0) {
        return "Hello, World!";
    }
    return "Not Found";
}

void run_application(void *env) {
    WSGIEnvironment *wsgi_env = (WSGIEnvironment *)env;
    WebApp *app = (WebApp *)wsgi_env->app;
    char *response = app->call(app, wsgi_env->request_path);
    printf("%s\n", response);
}

int main() {
    WebApp app = create_web_app();
    void *env = create_wsgi_environment(app, "/");
    run_application(env);
    free((WSGIEnvironment *)env);
    return 0;
}