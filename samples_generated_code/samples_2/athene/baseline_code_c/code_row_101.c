#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* name;
} Environment;

typedef struct {
    const char* content_type;
    const char* body;
} Response;

Response render_response_from_env(Environment *env) {
    const char *name = getenv("USER_NAME"); // Assume this is set in the environment for the request
    if (name == NULL) name = "World";
    
    const char *template = env->name; // Simplified, assuming env->name holds the template string
    
    size_t body_len = strlen(template) + strlen(name) + 10;
    char *body = malloc(body_len);
    snprintf(body, body_len, template, name);

    Response response = {
        .content_type = "text/html",
        .body = body
    };
    return response;
}

Response home(Environment *env) {
    return render_response_from_env(env);
}