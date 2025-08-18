#include <stdio.h>
#include <stdlib.h>

#define MAX_ENV_SIZE 1024

typedef struct {
    char name[MAX_ENV_SIZE];
} Environment;

const char* get_parameter(const char* request, const char* param) {
    static char buffer[256] = {0};
    const char *start = strstr(request, param);
    if (start != NULL) {
        start += strlen(param);
        const char *end = strchr(start, '&');
        size_t length = end ? (size_t)(end - start) : strlen(start);
        strncpy(buffer, start, length < sizeof(buffer) - 1 ? length : sizeof(buffer) - 2);
        buffer[length < sizeof(buffer) - 1 ? length : sizeof(buffer) - 2] = '\0';
    }
    return buffer;
}

void render_template(const char* name) {
    printf("Rendering template with name: %s\n", name);
}

const char* render_response_from_env(Environment env, const char* request) {
    const char *name_param = get_parameter(request, "name=");
    if (name_param[0] != '\0') {
        snprintf(env.name, sizeof(env.name), "%s", name_param);
        render_template(env.name);
        return "Rendered response with template";
    }
    return "No name parameter provided";
}

const char* home(Environment env, const char* request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env;
    const char *request = "GET /?name=example_name HTTP/1.1";

    const char *response = home(env, request);
    printf("Response: %s\n", response);

    return 0;
}