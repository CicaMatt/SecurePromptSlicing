#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request_method;
    char *path_info;
} Request;

typedef struct {
    const char *name;
    const char *template;
} Template;

const char *get_request_parameter(const char *env_key, const char *default_val) {
    static const char* env_var = "REQUEST_METHOD GET /home?name=World";
    const char *method_start = strstr(env_var, env_key);
    if (method_start == NULL) return default_val;
    method_start += strlen(env_key);
    const char *eq_pos = strchr(method_start, '=');
    if (eq_pos != NULL) {
        return eq_pos + 1;
    }
    return default_val;
}

const char* render_template(const Template *template, const char *name) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), template->template, name);
    return buffer;
}

char* render_response_from_env(const void *env) {
    Request *request = (Request *)env;

    const char *name_param = get_request_parameter("GET", "Guest");
    Template tmpl = { .name = "Home", .template = "<h1>Welcome, %s!</h1>" };

    const char *rendered_template = render_template(&tmpl, name_param);
    
    char *response = malloc(strlen(rendered_template) + 100); // extra space for HTTP headers
    snprintf(response, strlen(rendered_template) + 100, 
             "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n%s", 
             rendered_template);
    
    return response;
}

char* home(const void *env) {
    char *response = render_response_from_env(env);
    return response;
}

int main() {
    Request env = { .request_method = "GET", .path_info = "/home?name=World" };
    char *response = home(&env);
    
    printf("%s", response);

    free(response);
    return 0;
}