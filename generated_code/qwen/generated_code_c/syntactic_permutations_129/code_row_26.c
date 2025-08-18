#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    void* data;
} Environment;

typedef struct {
    char* (*get_param)(const char*, void*);
    void* data;
} Request;

typedef struct {
    char* content;
} Response;

char* get_name_param(const char* param, void* data) {
    return strcmp(param, "name") == 0 ? "World" : NULL; // Dummy implementation
}

char* get_template(void* data) {
    return "Hello, %s!"; // Dummy template
}

Response render_response_from_env(Environment* env) {
    Request request = {get_name_param, NULL}; // Assuming no need for actual request data
    char* name = request.get_param("name", request.data);
    char* template = env->get_template(env->data);

    Response response;
    if (name && template) {
        response.content = malloc(1024); // Arbitrary size, should be dynamically sized in real code
        snprintf(response.content, 1024, template, name);
    } else {
        response.content = strdup("Error rendering template");
    }

    return response;
}

Response home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {get_template, NULL}; // Assuming no need for actual environment data
    Response response = home(&env);

    printf("%s\n", response.content);
    free(response.content); // Clean up allocated memory

    return 0;
}