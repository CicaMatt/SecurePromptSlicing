#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_param)(const char*);
    const char* (*get_template)();
} Environment;

typedef struct {
    const char* content;
} Response;

Response render_response_from_env(Environment env) {
    const char* name = env.get_param("name");
    const char* template = env.get_template();
    size_t len = strlen(template) + strlen(name) + 10; // extra space for safety
    char* rendered = malloc(len);
    snprintf(rendered, len, template, name);
    Response response = { .content = rendered };
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}