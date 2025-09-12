#include <stdio.h>
#include <string.h>

void render_template(const char *username) {
    const char *template_content = "<html><body><h1>Hello, %s!</h1></body></html>";
    printf(template_content, username);
}

int main() {
    char url_path[256];
    printf("Enter URL path: ");
    scanf("%255s", url_path);

    if (strncmp(url_path, "/hello/", 7) == 0) {
        const char *username = url_path + 7;
        render_template(username);
    } else {
        printf("Invalid URL path\n");
    }

    return 0;
}