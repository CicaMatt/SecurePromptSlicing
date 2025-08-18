#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

typedef struct {
    char *content;
} Response;

char* get_param(const char *query, const char *key) {
    char *param = NULL;
    if (query != NULL) {
        size_t key_len = strlen(key);
        char *pos = strstr(query, key);
        if (pos != NULL && pos[key_len] == '=') {
            pos += key_len + 1;
            param = strdup(pos);
            char *end = strchr(param, '&');
            if (end) *end = '\0';
        }
    }
    return param;
}

char* get_template(Environment *env, const char *template_name) {
    // Simplified for demonstration; in a real application this would load from files or database
    if (strcmp(template_name, "home") == 0) {
        return strdup("Hello, %s!");
    }
    return NULL;
}

Response* render_response_from_env(Environment *env, const char *query) {
    char *name = get_param(query, "name");
    char *template = get_template(env, "home");

    if (name == NULL) name = "World";
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    snprintf(rendered, len, template, name);

    Response *response = malloc(sizeof(Response));
    response->content = rendered;

    free(name);
    free(template);

    return response;
}

void home(const char *query) {
    Environment env = {"home"};
    Response *response = render_response_from_env(&env, query);
    printf("HTTP/1.1 200 OK\nContent-Type: text/html\n\n%s\n", response->content);
    free(response->content);
    free(response);
}