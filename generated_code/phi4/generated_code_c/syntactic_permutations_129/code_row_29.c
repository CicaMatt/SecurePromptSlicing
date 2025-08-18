#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_parameter(const char* request, const char* param_name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%s=", param_name);
    const char *start = strstr(request, buffer);

    if (start) {
        start += strlen(buffer);
        char *end = strchr(start, '&');
        if (!end) end = request + strlen(request);
        
        size_t length = end - start;
        char *result = malloc(length + 1);
        strncpy(result, start, length);
        result[length] = '\0';
        return result;
    }
    
    return NULL;
}

char* render_template(const char* template, const char* name) {
    if (template == NULL || name == NULL) return NULL;

    size_t buffer_size = strlen(template) + strlen(name) + 2; // for the substitution
    char *buffer = malloc(buffer_size);
    snprintf(buffer, buffer_size, "%s%s%s", template, "<name>", "</name>");
    
    char* result = strstr(buffer, "<name>");
    if (result) {
        char* end_tag = strstr(result, "</name>");
        size_t name_len = strlen(name);

        memmove(result + name_len + 1, result + strlen("<name>"), end_tag - result);
        memcpy(result, name, name_len);
    }

    free(buffer);
    return buffer;
}

char* render_response_from_env(Environment *env) {
    if (env == NULL || env->template == NULL) return NULL;

    char *rendered_template = render_template(env->template, env->name);
    return rendered_template ? strdup(rendered_template) : NULL;
}

char* home(const char* request, Environment *env) {
    const char* name_param = get_parameter(request, "name");
    if (name_param) {
        env->name = strdup(name_param);
    }

    char* response = render_response_from_env(env);
    free((void*)name_param);  // Free the dynamically allocated parameter

    return response;
}

int main() {
    Environment env = { .template = "Hello, <name>!" };
    
    const char *request = "GET /?name=World";
    char* response = home(request, &env);

    if (response) {
        printf("%s\n", response);
        free(response);
    }

    free(env.name);  // Clean up the dynamically allocated name

    return 0;
}