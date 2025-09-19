#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

const char* get_parameter(Request *request, const char *param) {
    if (strcmp(param, "name") == 0 && request->name != NULL) {
        return request->name;
    }
    return NULL;
}

char* render_template(const char *template_str, const char *name) {
    size_t len = strlen(template_str);
    char *rendered = malloc(len + strlen(name) + 1);

    if (rendered == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 0, j = 0; template_str[i] != '\0'; ++i) {
        if (template_str[i] == '{' && strncmp(&template_str[i], "{name}", 6) == 0) {
            strcpy(&rendered[j], name);
            i += 5;
            j += strlen(name);
        } else {
            rendered[j++] = template_str[i];
        }
    }

    rendered[j] = '\0';
    return rendered;
}

const char* render_response_from_env(Request *request, Environment *env) {
    const char *name_param = get_parameter(request, "name");
    if (name_param == NULL) {
        name_param = "(no name provided)";
    }
    return render_template(env->template, name_param);
}

void home() {
    Request request;
    request.name = "John Doe";

    Environment env;
    const char *template_str = "Hello, {name}! Welcome to the site.";
    env.template = template_str;

    const char *response = render_response_from_env(&request, &env);
    printf("%s\n", response);

    free((char *)response);  // Free memory allocated by render_template
}

int main() {
    home();
    return 0;
}