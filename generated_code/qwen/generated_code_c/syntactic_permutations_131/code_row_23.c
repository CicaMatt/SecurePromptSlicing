#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*get_template)(void*);
    char* (*render_template)(char*, char*);
} Environment;

char* get_user_name() {
    return "John Doe"; // Simulated user input
}

char* render_response_from_env(Environment* env) {
    char* name = get_user_name();
    char* template = env->get_template(env);
    char* rendered_template = env->render_template(template, name);

    return rendered_template;
}

char* get_home_template(void* env) {
    return "Hello, %s!";
}

char* render_home_template(char* template, char* name) {
    static char result[1024];
    snprintf(result, sizeof(result), template, name);
    return result;
}

char* home(Environment* env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {get_home_template, render_home_template};
    printf("%s\n", home(&env));
    return 0;
}