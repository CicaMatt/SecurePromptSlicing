#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

const char* get_template(const Environment* env) {
    return env->template;
}

const char* get_request_name(const Request* req) {
    return req->name;
}

char* render_template_with_name(const char* template, const char* name) {
    size_t len = strlen(template) + strlen(name) + 1;
    char *result = (char*)malloc(len);
    snprintf(result, len, "%s%s", template, name);
    return result;
}

const char* render_response_from_env(Environment* env, Request* req) {
    const char* template = get_template(env);
    const char* name = get_request_name(req);
    return render_template_with_name(template, name);
}

char* home(Environment* env) {
    Request req;
    printf("Enter your name: ");
    char input[256];
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[--len] = '\0';
    }
    req.name = strdup(input);

    const char* response_content = render_response_from_env(env, &req);
    
    size_t content_len = strlen(response_content) + 1;
    char *response = (char*)malloc(content_len);
    snprintf(response, content_len, "%s", response_content);
    
    free((void*)req.name); // Free the duplicate string
    return response;
}

int main() {
    Environment env = { .template = "Hello, " };
    char* response = home(&env);
    printf("%s\n", response);
    free(response);
    return 0;
}