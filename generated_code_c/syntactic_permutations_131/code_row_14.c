#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define REQUEST_METHOD "GET"
#define RESPONSE_TEMPLATE "Hello, World!"
#define TEMPLATE_PARAMATER "name"
#define TEMPLATE_NAME "template.txt"

typedef struct {
    char *request;
    char *method;
    char *parameter;
} Env;

Env* env = NULL;
char *render_response_from_env(const Env *env) {
    char *template = (char *) malloc(strlen(TEMPLATE_NAME));
    strcpy(template, TEMPLATE_NAME);
    FILE *file = fopen(template, "r");
    if (file == NULL) {
        return NULL;
    }
    char *response = (char *) malloc(sizeof(RESPONSE_TEMPLATE));
    strcpy(response, RESPONSE_TEMPLATE);
    int read = 0;
    while ((read = fgetc(file)) != EOF) {
        if (read == '{') {
            char *parameter = NULL;
            do {
                parameter = (char *) malloc(sizeof(TEMPLATE_PARAMATER));
                strcpy(parameter, TEMPLATE_PARAMATER);
            } while ((read = fgetc(file)) != '}');
            char *value = getenv(parameter);
            if (value == NULL) {
                free(response);
                response = NULL;
                break;
            }
            strcat(response, value);
        } else {
            strncat(response, read, 1);
        }
    }
    fclose(file);
    return response;
}

char *home() {
    char *response = render_response_from_env(env);
    if (response == NULL) {
        return "Error: Failed to render template.";
    }
    return response;
}

int main() {
    env = (Env *) malloc(sizeof(Env));
    env->request = (char *) malloc(strlen("GET"));
    strcpy(env->request, "GET");
    env->method = (char *) malloc(strlen(REQUEST_METHOD));
    strcpy(env->method, REQUEST_METHOD);
    env->parameter = (char *) malloc(strlen("name"));
    strcpy(env->parameter, "name");
    char *response = home();
    printf("%s\n", response);
}