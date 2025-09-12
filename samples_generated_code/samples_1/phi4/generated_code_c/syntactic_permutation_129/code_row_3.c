#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
    char *template;
} Environment;

char* render_template(const char *template, const char *name) {
    if (template == NULL || name == NULL) return NULL;
    
    size_t len = strlen(template) + strlen(name) + 1;
    char *rendered = malloc(len);
    if (!rendered) return NULL;
    
    snprintf(rendered, len, template, name);
    return rendered;
}

char* render_response_from_env(Environment env) {
    const char *name_param = "User";
    const char *template_str = "<html><body>Hello, %s!</body></html>";
    
    if (env.template == NULL) {
        env.template = template_str;
    }
    
    return render_template(env.template, name_param);
}

char* home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {NULL, "<html><body>Hello, %s!</body></html>"};
    
    char *response = home(env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    } else {
        printf("Error rendering response.\n");
    }
    
    return 0;
}