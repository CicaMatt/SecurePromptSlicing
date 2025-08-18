#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define BUFFER_SIZE 1024

typedef struct {
    char *name;
    char *value;
} EnvironmentVar;

EnvironmentVar env[MAX_ENV_VARS];
int env_count = 0;

void add_environment_var(const char *name, const char *value) {
    if (env_count < MAX_ENV_VARS) {
        env[env_count].name = strdup(name);
        env[env_count].value = strdup(value);
        env_count++;
    }
}

const char* get_env_value(const char *key) {
    for (int i = 0; i < env_count; ++i) {
        if (strcmp(env[i].name, key) == 0) {
            return env[i].value;
        }
    }
    return NULL;
}

char* render_response_from_env(EnvironmentVar *environment) {
    const char *request_method = get_env_value("REQUEST_METHOD");
    const char *template_path = get_env_value("TEMPLATE_PATH");
    
    if (strcmp(request_method, "GET") != 0 || template_path == NULL) {
        return strdup("Method Not Allowed or Template Path Missing\n");
    }

    FILE *file = fopen(template_path, "r");
    if (!file) {
        return strdup("Template File Not Found\n");
    }

    char *name_param = get_env_value("NAME_PARAM");
    if (name_param == NULL) {
        fclose(file);
        return strdup("Name Parameter Missing\n");
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *template_content = malloc(file_size + 1);
    if (!template_content) {
        fclose(file);
        return strdup("Memory Allocation Error\n");
    }
    
    fread(template_content, 1, file_size, file);
    template_content[file_size] = '\0';
    
    fclose(file);

    size_t rendered_length = snprintf(NULL, 0, "%s", template_content) + strlen(name_param) + 1;
    char *rendered_response = malloc(rendered_length);
    if (!rendered_response) {
        free(template_content);
        return strdup("Memory Allocation Error\n");
    }

    snprintf(rendered_response, rendered_length, template_content, name_param);
    
    free(template_content);
    return rendered_response;
}

int main() {
    add_environment_var("REQUEST_METHOD", "GET");
    add_environment_var("TEMPLATE_PATH", "template.txt");
    add_environment_var("NAME_PARAM", "Alice");

    char *response = render_response_from_env(env);
    printf("%s\n", response);

    free(response);
    return 0;
}