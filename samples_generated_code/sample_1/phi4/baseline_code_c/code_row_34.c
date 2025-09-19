#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* get_request_name(Environment *env) {
    return env->name ? env->name : "Guest";
}

char* render_template(char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);

    // Allocate memory for the new string
    char *rendered = (char*)malloc(sizeof(char) * (template_len + name_len + 1));
    if (!rendered) return NULL;

    // Copy and replace placeholder with actual name
    const char *ptr = template;
    char *dest_ptr = rendered;

    while (*ptr) {
        if (strncmp(ptr, "{{name}}", 8) == 0) {
            memcpy(dest_ptr, name, name_len);
            dest_ptr += name_len;
            ptr += 8;
        } else {
            *(dest_ptr++) = *(ptr++);
        }
    }

    *dest_ptr = '\0';
    return rendered;
}

char* render_response_from_env(Environment env) {
    char *name_param = get_request_name(&env);
    if (!name_param) name_param = "Guest";

    char *rendered_template = render_template(env.template, name_param);
    free((void*)name_param);

    // Return the response with rendered template
    return rendered_template;
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "Alice", .template = "Hello, {{name}}!" };
    
    char *response = home(env);
    printf("%s\n", response);

    free(response); // Free the memory allocated for the rendered template
    return 0;
}