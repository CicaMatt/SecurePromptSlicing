#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *request;
    char *template;
} Environment;

char* render_template(Environment *env) {
    char *rendered = malloc(strlen(env->template) + strlen(env->request) + 1);
    if (rendered == NULL) {
        return NULL;
    }
    strcpy(rendered, env->template);
    strcat(rendered, env->request);
    return rendered;
}

char* render_response_from_env(Environment *env) {
    char *rendered = render_template(env);
    if (rendered == NULL) {
        return NULL;
    }
    char *response = malloc(strlen(rendered) + 10); // extra space for "Response: "
    if (response == NULL) {
        free(rendered);
        return NULL;
    }
    strcpy(response, "Response: ");
    strcat(response, rendered);
    free(rendered);
    return response;
}

char* home(Environment *env) {
    return render_response_from_env(env);
}

int main() {
    Environment env = {"GET /home", "<html><body>Welcome to the %s</body></html>"};
    char *response = home(&env);
    if (response != NULL) {
        printf("%s\n", response);
        free(response);
    }
    return 0;
}