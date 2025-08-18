#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Environment;

typedef struct {
    const char *template;
} Template;

typedef struct {
    const char *content;
} Response;

Response render_template(const char *template, const char *name) {
    size_t template_len = strlen(template);
    size_t name_len = strlen(name);
    size_t content_len = template_len + name_len + 1;
    
    char *content = (char *)malloc(content_len);
    snprintf(content, content_len, "%s%s", template, name);
    
    Response response = { .content = content };
    return response;
}

Response render_response_from_env(Environment env) {
    const char *template = "<html><body>Hello, %s!</body></html>";
    Template tmpl = { .template = template };
    
    Response response = render_template(tmpl.template, env.name);
    return response;
}

Response home(Environment env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = { .name = "World" };
    Response response = home(env);
    
    printf("%s\n", response.content);
    free((void *)response.content); // Free the allocated memory
    
    return 0;
}