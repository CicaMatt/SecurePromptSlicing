#include <stdio.h>
#include <string.h>

typedef struct {
    char *url;
    void (*handler)(char *);
} Route;

void render_template(const char *template, const char *username) {
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t pos = 0;
        while ((pos = strstr(buffer + pos, "{{username}}")) != NULL) {
            memmove(pos, pos + strlen("{{username}}"), strlen(pos + strlen("{{username}}")) + 1);
            strncpy(pos, username, strlen(username));
        }
        printf("%s", buffer);
    }
    fclose(file);
}

void hello_handler(char *username) {
    render_template("hello.html", username);
}

Route routes[] = {
    {"/hello/", hello_handler},
};

void dispatch(const char *url, const char *username) {
    for (int i = 0; i < sizeof(routes)/sizeof(routes[0]); i++) {
        if (strncmp(url, routes[i].url, strlen(routes[i].url)) == 0) {
            routes[i].handler(username);
            return;
        }
    }
}

int main() {
    const char *url = "/hello/john";
    const char *username = url + strlen("/hello/");
    dispatch(url, username);
    return 0;
}