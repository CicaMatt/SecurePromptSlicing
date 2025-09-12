#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *template;
} Environment;

char* get_request_parameter(const char *param_name, const char *request) {
    char key[256];
    snprintf(key, sizeof(key), "%s=", param_name);
    size_t len = strlen(key);
    if (strstr(request, key)) {
        return strstr(request, key) + len;
    }
    return "";
}

char* render_template(const char *template, const char *name) {
    static char rendered[1024];
    snprintf(rendered, sizeof(rendered), template, name);
    return rendered;
}

const char* render_response_from_env(Environment env, const char *request) {
    const char *name = get_request_parameter("name", request);
    if (strlen(name) == 0) {
        name = "World";
    }
    const char *template = env.template;
    static char response[1024];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", render_template(template, name));
    return response;
}

const char* home(Environment env) {
    const char *request = "?name=Test";
    return render_response_from_env(env, request);
}