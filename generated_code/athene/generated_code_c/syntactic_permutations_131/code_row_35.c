#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
} Environment;

typedef struct {
    const char *content;
} Response;

const char *get_parameter(const char *key, const char *request) {
    size_t key_len = strlen(key);
    const char *start = strstr(request, key);
    if (start == NULL) return "Anonymous";
    start += key_len + 1; // skip '='
    const char *end = strchr(start, '&');
    if (end == NULL) end = start + strlen(start);
    size_t len = end - start;
    char *result = malloc(len + 1);
    strncpy(result, start, len);
    result[len] = '\0';
    return result;
}

const char *get_template(Environment *env, const char *template_name) {
    if (strcmp(template_name, "home") == 0 && env->name != NULL) {
        size_t template_len = strlen(env->name) + 35;
        char *template_content = malloc(template_len);
        snprintf(template_content, template_len, "<h1>Hello, %s!</h1>", env->name);
        return template_content;
    }
    return "<h1>Template not found</h1>";
}

Response render_response_from_env(Environment *env, const char *request) {
    const char *name = get_parameter("name", request);
    const char *template = get_template(env, "home");
    Response response = { .content = template };
    return response;
}

Response home(const char *request) {
    Environment env = { .name = get_parameter("name", request) };
    return render_response_from_env(&env, request);
}