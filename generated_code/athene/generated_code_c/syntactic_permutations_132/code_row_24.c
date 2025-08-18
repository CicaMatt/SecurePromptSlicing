#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    char *value;
} KeyValue;

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

KeyValue *create_key_value(char *key, char *value) {
    KeyValue *kv = (KeyValue *)malloc(sizeof(KeyValue));
    kv->key = key;
    kv->value = value;
    return kv;
}

void free_key_value(KeyValue *kv) {
    free(kv->key);
    free(kv->value);
    free(kv);
}

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

char *render_template(const char *template_path, KeyValue *kv) {
    char *template_content = read_file(template_path);
    size_t template_len = strlen(template_content);
    size_t value_len = strlen(kv->value);
    char *rendered = malloc(template_len + value_len + 1);
    int i = 0, j = 0;
    while (i < template_len) {
        if (template_content[i] == '{' && template_content[i+1] == '{') {
            i += 2;
            while (j < value_len) {
                rendered[j++] = kv->value[j-2];
            }
            i++;
        } else {
            rendered[j++] = template_content[i++];
        }
    }
    rendered[j] = '\0';
    free(template_content);
    return rendered;
}

void hello(char *username) {
    KeyValue *kv = create_key_value("username", username);
    char *rendered_template = render_template("hello.html", kv);
    printf("%s\n", rendered_template);
    free(rendered_template);
    free_key_value(kv);
}

void route_handler(Route *route, char *url_path, char *username) {
    if (strcmp(route->url, url_path) == 0) {
        route->handler(username);
    }
}

int main() {
    Route routes[] = {
        {"/hello/", hello}
    };
    int num_routes = sizeof(routes) / sizeof(routes[0]);
    char *url_path = "/hello/";
    char *username = "JohnDoe";
    for (int i = 0; i < num_routes; i++) {
        route_handler(&routes[i], url_path, username);
    }
    return 0;
}