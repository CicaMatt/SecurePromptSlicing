#include <stdio.h>
#include <stdlib.h>

// Define a basic WSGI-compatible handler structure and functions
typedef struct {
    void (*start_response)(const char *status, const char *headers[], int num_headers);
} WSGIEnvironment;

void simple_start_response(WSGIEnvironment *env, const char *status, const char *headers[], int num_headers) {
    printf("Status: %s\n", status);
    for (int i = 0; i < num_headers; ++i) {
        printf("%s\n", headers[i]);
    }
}

typedef struct _app_t app_t;
struct _app_t {
    void (*run)(WSGIEnvironment *);
};

// The WSGI application function
static void hello_app(WSGIEnvironment *env) {
    simple_start_response(env, "200 OK", (const char*[]){"Content-Type: text/plain\0"}, 1);
    printf("Hello World!\n");
}

// Function to create the WSGI application object
app_t create_wsgi_application(void (*function)(WSGIEnvironment *)) {
    app_t app = { .run = function };
    return app;
}

int main(int argc, char *argv[]) {
    // Create the WSGI application instance
    WSGIEnvironment env;
    app_t wsgi_app = create_wsgi_application(hello_app);

    // Run the application with a simulated environment
    wsgi_app.run(&env);
    
    return 0;
}