#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024

typedef struct {
    char* request_method;
    char* path_info;
    char* query_string;
} Request;

typedef struct {
    Request* request;
    void* other_data; // Placeholder for additional environment data
} Environment;

char* get_param(const char *request_line, const char *param) {
    if (strncmp(request_line, param, strlen(param)) != 0 || request_line[strlen(param)] != '=') {
        return NULL;
    }
    return strdup(request_line + strlen(param) + 1);
}

char* render_template(const char *template) {
    // Simple example of rendering: just copy the template
    char* rendered = (char*)malloc(MAX_TEMPLATE_SIZE);
    if (rendered == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(rendered, template, MAX_TEMPLATE_SIZE - 1);
    rendered[MAX_TEMPLATE_SIZE - 1] = '\0';
    return rendered;
}

void render_response_from_env(Environment *env, char **response_out) {
    const char* name = get_param(env->request->query_string, "name");
    char *template;

    if (strcmp(env->request->path_info, "/home") == 0) {
        template = "Hello, ";
    } else {
        template = "Welcome to the site!";
    }
    
    if (name != NULL) {
        char full_template[MAX_TEMPLATE_SIZE];
        snprintf(full_template, MAX_TEMPLATE_SIZE, "%s%s!", template, name);
        template = full_template;
    }

    *response_out = render_template(template);

    if (name != NULL) {
        free((void*)name);
    }
}

char* home(Environment *env) {
    char *response;
    render_response_from_env(env, &response);
    return response;
}

int main() {
    Environment env;
    Request req;

    // Simulate a request with query string
    req.request_method = "GET";
    req.path_info = "/home";
    req.query_string = "name=John";

    env.request = &req;

    char *response = home(&env);
    
    printf("%s\n", response);

    free(response);

    return 0;
}