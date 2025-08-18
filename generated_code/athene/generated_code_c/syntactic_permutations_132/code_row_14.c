#include <stdio.h>
#include <string.h>

typedef struct {
    char* url;
    void (*handler)(char* username);
} Route;

void render_template(char* template_file, char* username) {
    FILE *file = fopen(template_file, "r");
    if (file == NULL) return;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char output[256] = "";
        if (strstr(line, "{{username}}")) {
            strcpy(output, str_replace(line, "{{username}}", username));
        } else {
            strcpy(output, line);
        }
        printf("%s", output);
    }
    fclose(file);
}

char* str_replace(const char *s, const char *sub, const char *rep) {
    char *token = NULL;
    char *buff = NULL;
    int i, count = 0;

    for (i = 0; s[i] != '\0'; ++i)
        if (strstr(&s[i], sub) == &s[i]) {
            count++;
            i += strlen(sub) - 1;
        }

    buff = malloc(strlen(s) + ((strlen(rep) - strlen(sub)) * count) + 1);
    if (!buff) return NULL;

    while (*s) {
        if (strstr(s, sub) == s) {
            strcpy(buff, rep);
            buff += strlen(rep);
            s += strlen(sub);
        } else
            *buff++ = *s++;
    }
    *buff = '\0';
    return buff - (strlen(s) + ((strlen(rep) - strlen(sub)) * count));
}

void user_handler(char* username) {
    render_template("user.html", username);
}

void route_add(Route routes[], int *route_count, const char *url, void (*handler)(char* username)) {
    routes[*route_count].url = strdup(url);
    routes[*route_count].handler = handler;
    (*route_count)++;
}

void dispatch_request(Route routes[], int route_count, const char *request_url) {
    for (int i = 0; i < route_count; ++i) {
        if (strstr(request_url, routes[i].url)) {
            char username[128];
            sscanf(request_url, "%*[^/]/%s", username);
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    Route routes[10];
    int route_count = 0;

    route_add(routes, &route_count, "/<username>", user_handler);

    char request_url[] = "/john_doe";
    dispatch_request(routes, route_count, request_url);

    return 0;
}