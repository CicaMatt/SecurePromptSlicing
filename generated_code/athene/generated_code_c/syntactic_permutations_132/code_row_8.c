#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
} RequestContext;

void render_template(char *template_file, char *username) {
    FILE *fp = fopen(template_file, "r");
    if (fp == NULL) return;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);

    printf("<h1>Welcome %s</h1>", username);
}

typedef void (*Handler)(RequestContext *);

void url_decorator(char *url_pattern, Handler handler) {
    char input[1024];
    printf("Enter the URL: ");
    scanf("%s", input);

    if (strstr(input, url_pattern)) {
        RequestContext ctx;
        sscanf(input, "%*[^/]/%s", ctx.username);
        handler(&ctx);
    }
}

void user_handler(RequestContext *ctx) {
    render_template("template.html", ctx->username);
}

int main() {
    url_decorator("/<username>", user_handler);
    return 0;
}