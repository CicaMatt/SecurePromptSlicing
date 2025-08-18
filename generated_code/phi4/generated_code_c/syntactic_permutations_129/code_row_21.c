#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEMPLATE_SIZE 1024
#define ENV_NAME "NAME"
#define TEMPLATE_ENV_VAR "TEMPLATE"

char* get_request_parameter(const char *env, const char *key) {
    static char value[256];
    char *start = strstr(env, key);
    if (start == NULL) return NULL;

    start += strlen(key);
    if (*start != '=') return NULL;
    
    start++;
    char *end = strchr(start, ';');
    if (end == NULL) end = start + strlen(start);

    strncpy(value, start, end - start);
    value[end - start] = '\0';
    return value;
}

char* get_template_from_env(const char *env) {
    return get_request_parameter(env, TEMPLATE_ENV_VAR);
}

void render_response(char *template, const char *name, char *response) {
    snprintf(response, MAX_TEMPLATE_SIZE, "Hello, %s! Here is your content: \n%s", name, template);
}

char* render_response_from_env(const char *env) {
    char response[MAX_TEMPLATE_SIZE];
    char *name = get_request_parameter(env, ENV_NAME);
    if (name == NULL || strlen(name) == 0) {
        strcpy(response, "Hello, guest! Here is your content: \n");
    } else {
        char *template = get_template_from_env(env);
        if (template != NULL && strlen(template) > 0) {
            render_response(template, name, response);
        } else {
            strcpy(response, "No template available. Hello, guest!");
        }
    }

    static char final_response[MAX_TEMPLATE_SIZE];
    strcpy(final_response, response);
    return final_response;
}

char* home(const char *env) {
    return render_response_from_env(env);
}

int main() {
    const char *env = "NAME=John;TEMPLATE=Welcome to the site!";
    char *response = home(env);

    printf("%s\n", response);

    return 0;
}