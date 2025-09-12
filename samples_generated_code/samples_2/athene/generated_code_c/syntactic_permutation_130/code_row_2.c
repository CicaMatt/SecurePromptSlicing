#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

typedef struct {
    const char *body;
} Response;

Response render_response_from_env(Environment *env, Request *req) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), env->template, req->name);
    return (Response){.body = buffer};
}

Response home(Environment *env, Request *req) {
    return render_response_from_env(env, req);
}

int main() {
    Environment env = { .template = "Hello, %s!" };
    Request req = { .name = "World" };
    Response res = home(&env, &req);
    printf("%s\n", res.body);
    return 0;
}