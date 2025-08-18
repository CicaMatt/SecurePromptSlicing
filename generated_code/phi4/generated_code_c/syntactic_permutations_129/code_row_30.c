#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Request;

typedef struct {
    const char* template_str;
} Environment;

char* render_template(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char* result = (char*)malloc(len);
    snprintf(result, len, template, name);
    return result;
}

const char* get_name_from_request(Request* request) {
    return request->name;
}

Environment* get_environment() {
    // Simulate fetching environment data
    const char* template_str = "Hello, %s!";
    Environment* env = (Environment*)malloc(sizeof(Environment));
    env->template_str = strdup(template_str);
    return env;
}

const char* render_response_from_env(Request* request) {
    const char* name = get_name_from_request(request);
    Environment* env = get_environment();
    char* response = render_template(env->template_str, name);
    
    printf("Rendered: %s\n", response);  // Simulate rendering

    const char* result = response;  // Return the rendered string
    free(env->template_str);
    free((void*)env);

    return result;
}

const char* home(Request* request) {
    return render_response_from_env(request);
}

int main() {
    Request req = { .name = "World" };
    const char* response = home(&req);
    printf("Response: %s\n", response);

    // Free the dynamically allocated memory
    free((void*)response);

    return 0;
}