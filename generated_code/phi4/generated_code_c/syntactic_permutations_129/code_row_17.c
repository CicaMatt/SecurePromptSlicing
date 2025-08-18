#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    int num_headers;
} Response;

typedef struct {
    char *name;
} Request;

typedef struct {
    Request request;
    // Additional environment fields can be added here
} Environment;

Response render_template_with_name(const char *template, const char *name) {
    Response response;
    size_t len = snprintf(NULL, 0, "%s: %s", template, name);
    char *rendered = malloc(len + 1);
    sprintf(rendered, "%s: %s", template, name);

    response.headers = malloc(sizeof(char*) * 2);
    response.headers[0] = strdup("Content-Type");
    response.headers[1] = strdup("text/plain");

    response.num_headers = 2;
    printf("%s\n", rendered); // Simulate sending the response
    free(rendered);

    return response;
}

Response render_response_from_env(Environment env) {
    const char *name = env.request.name ? env.request.name : "default";
    const char *template = "Template Content";

    return render_template_with_name(template, name);
}

Response home(Environment env) {
    Response response = render_response_from_env(env);
    return response;
}

int main() {
    Environment env;
    env.request.name = strdup("ExampleName");

    Response response = home(env);

    for (int i = 0; i < response.num_headers; ++i) {
        printf("%s\n", response.headers[i]);
        free(response.headers[i]);
    }
    
    free(response.headers);
    free(env.request.name);

    return 0;
}