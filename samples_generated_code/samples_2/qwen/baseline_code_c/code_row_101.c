#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char* (*get_template)(const char*);
    const char* (*get_request_param)(const char*, const char*);
} Environment;

const char* get_template(const char* template_name) {
    // This is a mock implementation. In a real scenario, this function would fetch the template from a file or database.
    if (strcmp(template_name, "home") == 0) {
        return "<html><body>Hello, %s!</body></html>";
    }
    return NULL;
}

const char* get_request_param(const char* request, const char* param_name) {
    // This is a mock implementation. In a real scenario, this function would parse the request to find the parameter.
    if (strcmp(param_name, "name") == 0 && strstr(request, "name=")) {
        return strstr(request, "name=") + strlen("name=");
    }
    return NULL;
}

const char* render_response_from_env(const Environment* env, const char* request) {
    const char* name = env->get_request_param(request, "name");
    const char* template = env->get_template("home");

    if (name && template) {
        static char response[256];
        snprintf(response, sizeof(response), template, name);
        return response;
    }
    return "<html><body>Error rendering template</body></html>";
}

const char* home(const Environment* env, const char* request) {
    return render_response_from_env(env, request);
}

int main() {
    Environment env = {get_template, get_request_param};
    const char* request = "GET /?name=World HTTP/1.1";
    const char* response = home(&env, request);
    printf("%s\n", response);
    return 0;
}