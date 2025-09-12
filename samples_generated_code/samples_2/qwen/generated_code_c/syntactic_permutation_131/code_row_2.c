#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMPLATE_BUFFER_SIZE 1024

typedef struct {
    const char* query_string;
} Environment;

const char* get_query_parameter(const char* query_string, const char* param_name) {
    char param[256];
    snprintf(param, sizeof(param), "%s=", param_name);
    const char* param_start = strstr(query_string, param);
    if (param_start != NULL) {
        param_start += strlen(param);
        const char* param_end = strchr(param_start, '&');
        size_t param_length = param_end ? param_end - param_start : strlen(param_start);
        char* value = malloc(param_length + 1);
        strncpy(value, param_start, param_length);
        value[param_length] = '\0';
        return value;
    }
    return NULL;
}

const char* render_template(const char* name) {
    static char buffer[TEMPLATE_BUFFER_SIZE];
    snprintf(buffer, TEMPLATE_BUFFER_SIZE, "<html><body><h1>Hello, %s!</h1></body></html>", name);
    return buffer;
}

const char* render_response_from_env(Environment env) {
    const char* name = get_query_parameter(env.query_string, "name");
    if (name == NULL) {
        name = "Guest";
    }
    const char* response = render_template(name);
    free((void*)name); // Free the allocated memory for the parameter value
    return response;
}

const char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .query_string = "name=John" };
    const char* response = home(env);
    printf("%s\n", response);
    return 0;
}