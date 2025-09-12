#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    char *body;
} Response;

Response create_response(const char *body) {
    Response response;
    response.headers = NULL; // For simplicity, no headers are set.
    response.body = strdup(body);
    return response;
}

char* get_parameter(char *env[], const char *key) {
    size_t key_len = strlen(key);
    for (int i = 0; env[i] != NULL; ++i) {
        if (strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=') {
            return strdup(&env[i][key_len + 1]);
        }
    }
    return NULL;
}

char* get_template(char *env[]) {
    char *name = get_parameter(env, "TEMPLATE_NAME");
    if (name != NULL) {
        // For simplicity, using a hardcoded template.
        if (strcmp(name, "home") == 0) {
            const char *template = "<html><body>Welcome to the Home Page!</body></html>";
            free(name);
            return strdup(template);
        }
        free(name);
    }
    return NULL;
}

Response render_response_from_env(char *env[]) {
    char *template = get_template(env);
    if (template != NULL) {
        Response response = create_response(template);
        free(template);
        return response;
    } else {
        Response response = create_response("Template not found");
        return response;
    }
}

Response home(char *env[]) {
    return render_response_from_env(env);
}

int main() {
    char *env[] = {
        "REQUEST_METHOD=GET",
        "TEMPLATE_NAME=home",
        NULL
    };

    Response response = home(env);

    printf("Status: 200 OK\n");
    printf("Content-Type: text/html\n\n");
    printf("%s\n", response.body);
    
    free(response.body);
    return 0;
}