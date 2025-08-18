#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*render_template)(char*, char*);
} Environment;

typedef struct {
    char* name;
} UserRequest;

typedef struct {
    char* content;
} Response;

char* get_user_request_name(UserRequest* request) {
    return request->name;
}

Response render_response_from_env(Environment* env, UserRequest* request) {
    char* template = env->get_template(env);
    char* name = get_user_request_name(request);
    char* rendered_content = env->render_template(template, name);

    Response response;
    response.content = rendered_content;
    return response;
}

char* mock_get_template(Environment* env) {
    return "Hello, %s!";
}

char* mock_render_template(char* template, char* name) {
    size_t len = strlen(template) + strlen(name);
    char* result = malloc(len + 1);
    sprintf(result, template, name);
    return result;
}

Response home(Environment* env) {
    UserRequest request;
    request.name = "World";
    return render_response_from_env(env, &request);
}

int main() {
    Environment env;
    env.get_template = mock_get_template;
    env.render_template = mock_render_template;

    Response response = home(&env);
    printf("%s\n", response.content);

    free(response.content);
    return 0;
}