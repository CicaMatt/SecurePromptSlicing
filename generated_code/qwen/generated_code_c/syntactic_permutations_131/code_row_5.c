#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define TEMPLATE_SIZE 256

char* get_template() {
    return "Hello, %s!";
}

char* get_name_parameter(char* request) {
    char* name_start = strstr(request, "name=");
    if (name_start != NULL) {
        name_start += strlen("name=");
        char* name_end = strchr(name_start, '&');
        if (name_end == NULL) {
            name_end = name_start + strlen(name_start);
        }
        size_t name_length = name_end - name_start;
        char* name = malloc((name_length + 1) * sizeof(char));
        strncpy(name, name_start, name_length);
        name[name_length] = '\0';
        return name;
    }
    return NULL;
}

char* render_response_from_env(char* env) {
    char* request = getenv(env);
    if (request == NULL) {
        return "Invalid request";
    }

    char* name = get_name_parameter(request);
    if (name == NULL) {
        return "Name parameter not found";
    }

    char* template = get_template();
    char* response = malloc(TEMPLATE_SIZE * sizeof(char));
    snprintf(response, TEMPLATE_SIZE, template, name);

    free(name);
    return response;
}

char* home(char* env) {
    return render_response_from_env(env);
}

int main() {
    setenv("REQUEST", "name=World&otherparam=value", 1);
    char* response = home("REQUEST");
    printf("%s\n", response);
    free(response);
    return 0;
}