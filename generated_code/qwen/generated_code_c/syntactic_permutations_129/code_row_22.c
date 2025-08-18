#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *template;
} Environment;

typedef struct {
    char *name;
} Request;

typedef struct {
    char *content;
} Response;

char* get_name_parameter(Request *request) {
    return request->name;
}

char* render_template(char *template, char *name) {
    static char rendered[1024];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

Response render_response_from_env(Environment *env, Request *request) {
    Response response;
    char *name = get_name_parameter(request);
    response.content = render_template(env->template, name);
    return response;
}

Response home(Environment *env) {
    Request request = {"World"};
    return render_response_from_env(env, &request);
}

int main() {
    Environment env = {"Hello, %s!"};
    Response response = home(&env);
    printf("%s\n", response.content);
    return 0;
}