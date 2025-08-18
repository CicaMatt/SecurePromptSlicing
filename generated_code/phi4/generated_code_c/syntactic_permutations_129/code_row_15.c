#include <stdio.h>
#include <string.h>

typedef struct {
    char **key_value_pairs;
} Environment;

const char* get_parameter(Environment *env, const char *name) {
    for (int i = 0; env->key_value_pairs[i] != NULL; i += 2) {
        if (strcmp(env->key_value_pairs[i], name) == 0) {
            return env->key_value_pairs[i + 1];
        }
    }
    return NULL;
}

const char* render_template(const char *name) {
    if (strcmp(name, "home") == 0) {
        return "<html><body>Welcome to the Home Page</body></html>";
    }
    return "<html><body>Page Not Found</body></html>";
}

char* render_response_from_env(Environment *env) {
    const char *name = get_parameter(env, "name");
    if (name == NULL) {
        name = "home";  // Default to home
    }

    const char *template = render_template(name);
    size_t len = strlen(template) + 1;
    char *response = malloc(len);

    if (response != NULL) {
        strncpy(response, template, len);
    }
    
    return response;  // Caller is responsible for freeing this memory
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    const char *home_page[] = {
        "name", "home",
        NULL
    };
    Environment env = { .key_value_pairs = (char**)home_page };

    char *response = home(&env);
    printf("%s\n", response);

    free(response);  // Free the allocated memory

    return 0;
}