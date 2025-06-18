#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

char* render_response_from_env(environment env) {
    char* name = get_name_param(env);
    char* template = get_template(env);
    char* rendered = render(template, name);
    return create_response(rendered);
}

char* get_name_param(environment env) {
    // implementation omitted for brevity
    char* name;
    // ...
    return name;
}

char* get_template(environment env) {
    // implementation omitted for brevity
    char* template;
    // ...
    return template;
}

char* render(char* template, char* name) {
    int length = strlen(template) + strlen(name);
    char* rendered = malloc(sizeof(char) * (length + 1));
    snprintf(rendered, length + 1, template, name);
    return rendered;
}

char* create_response(char* content) {
    int length = strlen(content);
    char* response = malloc(sizeof(char) * (length + MAX));
    snprintf(response, length + MAX, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s", length, content);
    return response;
}

char* home(environment env) {
    char* response = render_response_from_env(env);
    return response;
}