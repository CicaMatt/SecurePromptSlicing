#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* template;
} Environment;

char* get_name_parameter(Environment *env) {
    return env->name;
}

char* get_template(Environment *env) {
    return env->template;
}

char* render_template(char* template, const char* name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    
    // Allocate memory for the rendered output
    char* rendered = (char*)malloc(template_len + name_len + 1); // +1 for null terminator
    if (!rendered) return NULL;

    strcpy(rendered, template);
    strcat(rendered, name);

    return rendered;
}

char* render_response_from_env(Environment *env) {
    const char* name_param = get_name_parameter(env);
    char* template_str = get_template(env);
    
    char* rendered_output = render_template(template_str, name_param);
    
    if (!rendered_output) {
        printf("Error rendering template\n");
        return NULL;
    }

    return rendered_output;
}

char* home(Environment *env) {
    char* response = render_response_from_env(env);
    
    if (response) {
        return response;
    } else {
        return "Internal Server Error";
    }
}

int main() {
    Environment env;
    env.name = "User123";
    env.template = "Hello, ";

    char* result = home(&env);
    printf("%s\n", result);

    free(result); // Free the memory allocated by render_template

    return 0;
}