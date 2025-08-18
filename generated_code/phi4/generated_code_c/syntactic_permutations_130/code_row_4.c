#include <stdio.h>
#include <string.h>

#define ENV_MAX_SIZE 1024

typedef struct {
    char name[256];
    char template[ENV_MAX_SIZE];
} Environment;

char* get_name_from_request(const Environment *env) {
    // Simulate getting the "name" parameter from a request
    return env->name;
}

const char* get_template_from_env(const Environment *env) {
    // Simulate getting the template from the environment
    return env->template;
}

char* render_response(char *name, const char *template) {
    static char response[ENV_MAX_SIZE];
    snprintf(response, sizeof(response), template, name);
    return response;
}

const char* render_response_from_env(const Environment *env) {
    char *name = get_name_from_request(env);
    const char *template = get_template_from_env(env);
    return render_response(name, template);
}

const char* home(const Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env;
    strncpy(env.name, "John", sizeof(env.name));
    snprintf(env.template, sizeof(env.template), "Hello, %s!");

    const char *response = home(&env);
    printf("%s\n", response);

    return 0;
}