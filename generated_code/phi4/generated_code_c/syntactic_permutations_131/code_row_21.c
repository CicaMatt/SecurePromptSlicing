#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *content;
} Request;

typedef struct {
    char *response;
} Response;

Response render_template(Request *request, const char *template) {
    Response res;
    size_t tmpl_len = strlen(template);
    size_t req_len = strlen(request->content);
    res.response = malloc(tmpl_len + req_len + 1); // +1 for null terminator
    if (!res.response) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(res.response, template);
    strcat(res.response, request->content);
    return res;
}

Response render_response_from_env(Environment *env, Request *request) {
    Response response = render_template(request, env->template);
    return response;
}

Response home(Environment *env) {
    Request user_request = { .content = "This is the user's request content." };
    return render_response_from_env(env, &user_request);
}

int main() {
    Environment env = { .template = "Template: " };
    Response response = home(&env);

    printf("%s\n", response.response);
    free(response.response);

    return 0;
}