#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_SIZE 1024

typedef struct {
    char **headers;
    size_t headers_count;
} Response;

Response* create_response() {
    Response *response = (Response *)malloc(sizeof(Response));
    response->headers = NULL;
    response->headers_count = 0;
    return response;
}

void add_header(Response *response, const char *header) {
    if (!response || !header) return;
    
    size_t new_size = response->headers_count + 1;
    char **new_headers = (char **)realloc(response->headers, sizeof(char *) * new_size);
    if (new_headers) {
        response->headers = new_headers;
        response->headers[new_size - 1] = strdup(header);
        response->headers_count++;
    }
}

void free_response(Response *response) {
    if (!response) return;
    
    for (size_t i = 0; i < response->headers_count; ++i) {
        free(response->headers[i]);
    }
    free(response->headers);
    free(response);
}

char* get_env_variable(const char *name, const char **envp) {
    for (; *envp != NULL; ++envp) {
        if (strncmp(*envp, name "=", strlen(name) + 1) == 0) {
            return strdup(*envp + strlen(name) + 1);
        }
    }
    return NULL;
}

Response* render_response_from_env(const char **envp) {
    const char *name = get_env_variable("REQUEST_METHOD", envp);
    if (!name || strcmp(name, "GET") != 0) {
        Response *response = create_response();
        add_header(response, "Content-Type: text/plain");
        return response;
    }

    const char *template_var = get_env_variable("TEMPLATE", envp);
    const char *name_param = get_env_variable("NAME", envp);

    if (!template_var || !name_param) {
        Response *response = create_response();
        add_header(response, "Content-Type: text/plain");
        return response;
    }

    char *rendered_template = (char *)malloc(MAX_ENV_SIZE);
    snprintf(rendered_template, MAX_ENV_SIZE, "%s template with name %s", template_var, name_param);

    Response *response = create_response();
    add_header(response, "Content-Type: text/html");
    printf("%s\n", rendered_template); // Simulate response body output

    free(rendered_template);
    return response;
}

Response* home(const char **envp) {
    return render_response_from_env(envp);
}

int main(int argc, const char *argv[]) {
    const char *env[] = {
        "REQUEST_METHOD=GET",
        "TEMPLATE=Hello, {{name}}!",
        "NAME=Alice",
        NULL
    };

    Response *response = home(env);

    for (size_t i = 0; i < response->headers_count; ++i) {
        printf("%s\n", response->headers[i]);
    }

    free_response(response);
    return 0;
}