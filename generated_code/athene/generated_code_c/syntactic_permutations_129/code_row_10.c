#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *template_name;
} Environment;

typedef struct {
    char *request_data;
} Request;

typedef struct {
    char *content;
} Response;

Response* render_template(const char *template_name, const char *data) {
    // Simulate template rendering
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "Rendered: %s with data: %s", template_name, data);
    Response *response = (Response *)malloc(sizeof(Response));
    response->content = strdup(buffer);
    return response;
}

Response* render_response_from_env(Environment *env, Request *request) {
    const char *template_name = env->template_name;
    const char *data = request->request_data;
    return render_template(template_name, data);
}

Response* home(Environment *env) {
    Request request = { .request_data = "home request" };
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = { .template_name = "index.html" };
    Response *response = home(&env);
    printf("Response: %s\n", response->content);
    free(response->content);
    free(response);
    return 0;
}