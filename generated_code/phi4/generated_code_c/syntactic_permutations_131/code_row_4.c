#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
} Request;

typedef struct {
    const char *template;
} Environment;

const char* get_name_from_request(Request *request) {
    return request->name;
}

Environment* get_environment() {
    static Environment env = { "Hello, {{name}}!" };
    return &env;
}

char* render_template(const char *template_str, const char *name) {
    size_t template_len = strlen(template_str);
    size_t name_len = strlen(name);

    // Allocate memory for the result
    char *result = malloc(template_len + name_len - 4 + 1); // Adjust for "{{" and "}}" removal

    if (!result) return NULL;

    const char *src = template_str;
    char *dst = result;

    while (*src != '\0') {
        if (strncmp(src, "{{", 2) == 0) {
            src += 2; // Skip "{{"
            while (*src && strncmp(src, "}}", 2) != 0) {
                *dst++ = *src++;
            }
            if (*src == '\0') break;
            src += 2; // Skip "}}"
            strncpy(dst, name, name_len);
            dst += name_len;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';

    return result;
}

const char* render_response_from_env(Request request) {
    const char *name = get_name_from_request(&request);
    Environment *env = get_environment();
    
    char *rendered_template = render_template(env->template, name);

    // Normally we'd return the rendered template or store it in a response structure
    printf("Rendered Template: %s\n", rendered_template);

    free(rendered_template); // Free allocated memory for safety

    return "Response with Rendered Template";
}

const char* home(Request request) {
    return render_response_from_env(request);
}

int main() {
    Request user_request = { .name = "Alice" };
    const char *response = home(user_request);
    printf("Home Function Response: %s\n", response);

    return 0;
}