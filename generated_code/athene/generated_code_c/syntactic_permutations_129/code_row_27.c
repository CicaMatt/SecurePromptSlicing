#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

typedef struct {
    const char *template;
} Response;

char* get_request_parameter(const char *query, const char *param) {
    char *result = NULL;
    char key[256];
    snprintf(key, sizeof(key), "%s=", param);
    size_t key_len = strlen(key);
    if (strstr(query, key) == query) {
        result = strdup(query + key_len);
        char *end = strchr(result, '&');
        if (end) *end = '\0';
    }
    return result;
}

Response* render_response_from_env(Environment *env, const char *query) {
    Response *response = (Response *)malloc(sizeof(Response));
    char *name = get_request_parameter(query, "name");
    if (name == NULL) name = strdup("World");
    response->template = env->name ? env->name : "Hello, %s!";
    char *rendered = malloc(strlen(response->template) + strlen(name) + 1);
    sprintf(rendered, response->template, name);
    free(name);
    response->template = rendered;
    return response;
}

void home(Environment *env, const char *query) {
    Response *response = render_response_from_env(env, query);
    printf("%s\n", response->template);
    free((char *)response->template);
    free(response);
}