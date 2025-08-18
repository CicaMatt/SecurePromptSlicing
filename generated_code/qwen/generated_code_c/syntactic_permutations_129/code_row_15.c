#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
} Environment;

char* get_name_from_request(Environment* env) {
    return env->name;
}

char* render_template(char* name) {
    static char response[100];
    snprintf(response, sizeof(response), "Hello, %s!", name);
    return response;
}

char* render_response_from_env(Environment* env) {
    char* name = get_name_from_request(env);
    char* rendered_template = render_template(name);
    return rendered_template;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"World"};
    char* response = home(&env);
    printf("%s\n", response);
    return 0;
}