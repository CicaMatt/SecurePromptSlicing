#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
} Request;

typedef struct {
    Request *request;
} Environment;

typedef struct {
    char content[256];
} Response;

Response render_template(const char *name) {
    Response response;
    snprintf(response.content, sizeof(response.content), "<html><body>Hello, %s!</body></html>", name);
    return response;
}

Response render_response_from_env(Environment *env) {
    const char *name = env->request->name;
    return render_template(name);
}

Response home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Request request = {"World"};
    Environment env = {&request};
    Response response = home(&env);
    printf("%s\n", response.content);
    return 0;
}