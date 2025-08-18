#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_name(const char *request) {
    const char *prefix = "name=";
    size_t prefix_len = strlen(prefix);
    
    if (strncmp(request, prefix, prefix_len) != 0) {
        return NULL;
    }
    
    return strdup(request + prefix_len);
}

char* get_template(Environment env) {
    return env.template ? strdup(env.template) : strdup("Default template");
}

char* render_response(const char *name, const char *template) {
    size_t name_len = strlen(name) + 1;
    size_t template_len = strlen(template) + 1;
    
    char *response = (char *)malloc(name_len + template_len);
    if (!response) return NULL;
    
    strcpy(response, name);
    strcat(response, " - ");
    strcat(response, template);
    
    return response;
}

char* render_response_from_env(Environment env, const char *request) {
    char *name = get_name(request);
    if (name == NULL) {
        return strdup("Name parameter not found");
    }
    
    char *template = get_template(env);
    char *response = render_response(name, template);
    
    free(name);
    free(template);
    
    return response;
}

char* home(Environment env) {
    const char *request = "name=John";
    return render_response_from_env(env, request);
}

int main() {
    Environment env = { .template = "Welcome to the homepage!" };
    char *response = home(env);
    
    printf("%s\n", response);
    free(response);
    
    return 0;
}