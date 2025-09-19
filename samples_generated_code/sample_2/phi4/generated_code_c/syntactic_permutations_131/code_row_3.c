#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mocking a simple environment and template rendering system
typedef struct {
    char *name;
} Request;

typedef struct {
    const char *template_str;
} Template;

typedef struct {
    Request *request;
    Template *template_;
} Environment;

const char* render_template(const char *template_str, const char *name) {
    size_t name_len = strlen(name);
    size_t template_len = strlen(template_str);

    // Create a buffer for the rendered string
    char *rendered = malloc(template_len + name_len + 1); // +1 for '\0'
    if (!rendered) return NULL;

    const char *pos = template_str;
    char *out_pos = rendered;

    while (*pos != '\0') {
        if (strncmp(pos, "{{name}}", 8) == 0) {
            strncpy(out_pos, name, name_len);
            out_pos += name_len;
            pos += 8; // Skip the placeholder
        } else {
            *out_pos++ = *pos++;
        }
    }
    *out_pos = '\0';

    return rendered;
}

const char* render_response_from_env(Environment env) {
    const char *name = env.request->name;
    const char *template_str = env.template_->template_str;

    if (!name || !template_str) {
        return "Error: Missing parameters";
    }

    const char *rendered_template = render_template(template_str, name);
    if (!rendered_template) {
        return "Error: Rendering failed";
    }
    
    // Normally we would free this in real application after usage
    return rendered_template;
}

void home(Environment env) {
    const char* response = render_response_from_env(env);
    printf("Response:\n%s\n", response);

    // In a real scenario, you'd want to free the memory allocated by `render_template`
    // But since this is just an example, we'll skip that.
}

int main() {
    Request req = { "Alice" };
    Template tmpl = { "Hello, {{name}}!" };
    Environment env = { &req, &tmpl };

    home(env);

    return 0;
}