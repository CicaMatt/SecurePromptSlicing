#include <stdio.h>
#include <string.h>

typedef struct {
    char *name;
} Request;

void render_template(char *template, char *username) {
    printf("<html><body>");
    FILE *file = fopen("hello.html", "r");
    if (file == NULL) {
        printf("Template not found.");
    } else {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char *pos;
            if ((pos = strstr(line, "{{username}}")) != NULL) {
                int len = strlen(pos);
                memmove(pos + strlen(username), pos + 10, len - 10 + 1);
                strncpy(pos, username, strlen(username));
            }
            printf("%s", line);
        }
        fclose(file);
    }
    printf("</body></html>");
}

void hello(Request *request) {
    render_template("hello.html", request->name);
}

int main() {
    Request req = {"John Doe"};
    hello(&req);
    return 0;
}