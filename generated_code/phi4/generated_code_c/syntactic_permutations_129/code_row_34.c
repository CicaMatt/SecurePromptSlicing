#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **headers;
    size_t num_headers;
} Environment;

typedef struct {
    const char *name;
    int is_set;
} Parameter;

Parameter get_name_parameter(Environment *env) {
    for (size_t i = 0; i < env->num_headers; ++i) {
        if (strncmp(env->headers[i], "name=", 5) == 0) {
            return (Parameter){.name = &env->headers[i][5], .is_set = 1};
        }
    }
    return (Parameter){.name = NULL, .is_set = 0};
}

char* render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = name ? strlen(name) : 0;
    
    char *buffer = malloc(template_len + name_len + 1);
    if (!buffer) return NULL;

    const char *pos_template = template;
    const char *pos_name = name ? name : "";
    char *pos_buffer = buffer;

    while (*pos_template && *pos_name) {
        if (strncmp(pos_template, "{{name}}", 8) == 0) {
            strcpy(pos_buffer, pos_name);
            pos_buffer += name_len;
            pos_template += 8;
        } else {
            *pos_buffer++ = *pos_template++;
        }
    }

    strcpy(pos_buffer, pos_template);

    return buffer;
}

char* render_response_from_env(Environment *env) {
    Parameter param = get_name_parameter(env);
    const char *template_str = "Hello, {{name}}!";
    
    if (!param.is_set) {
        template_str = "Hello, Guest!";
    }
    
    char *rendered_template = render_template(template_str, param.name);
    return rendered_template;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    const size_t num_headers = 2;
    char *headers[] = {"name=John", "Content-Type:text/html"};

    Environment env = { .headers = headers, .num_headers = num_headers };

    char *response = home(&env);

    printf("%s\n", response);
    free(response); // Remember to free the allocated memory

    return 0;
}