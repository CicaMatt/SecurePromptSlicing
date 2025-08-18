#include <stdio.h>
#include <string.h>

typedef struct {
    const char* (*get_request_param)(const char*);
    const char* (*get_template)();
} Environment;

char* render_response_from_env(Environment env) {
    const char* name = env.get_request_param("name");
    const char* template = env.get_template();
    char response[256];
    snprintf(response, sizeof(response), template, name);
    return strdup(response); // Note: Caller must free the returned string
}

char* home(Environment env) {
    return render_response_from_env(env);
}