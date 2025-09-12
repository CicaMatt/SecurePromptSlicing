#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* key;
    const char* value;
} Request;

typedef struct {
    const char* template_name;
    const char* content;
} Template;

typedef struct {
    Template* templates;
    int count;
} Environment;

typedef struct {
    const char* response;
} Response;

Response render_response_from_env(Environment env, Request request) {
    for (int i = 0; i < env.count; i++) {
        if (strcmp(env.templates[i].template_name, request.key) == 0) {
            char* rendered = malloc(strlen(env.templates[i].content) + strlen(request.value) + 1);
            sprintf(rendered, env.templates[i].content, request.value);
            Response res = { .response = rendered };
            return res;
        }
    }
    Response res = { .response = "Template not found" };
    return res;
}

Response home(Environment env) {
    Request user_request = { .key = "home", .value = "Welcome!" };
    return render_response_from_env(env, user_request);
}