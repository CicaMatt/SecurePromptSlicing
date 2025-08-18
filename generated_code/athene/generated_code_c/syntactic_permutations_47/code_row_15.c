#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *root_dir;
} ServerContext;

typedef struct {
    const char *url;
    int (*handler)(ServerContext *, const char *);
} Route;

int send_file_to_browser(const char *file_path) {
    // Simulate sending file to browser
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) return -1; // File not found

    // Send the file content to the browser (simplified)
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *content = malloc(fsize + 1);
    fread(content, 1, fsize, fp);
    fclose(fp);
    content[fsize] = '\0';

    // Simulate sending to browser
    printf("Sending file: %s\nContent:\n%s\n", file_path, content);

    free(content);
    return 0;
}

int handle_image_request(ServerContext *ctx, const char *url) {
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/images/%s", ctx->root_dir, url + 1); // Skip leading '/'

    if (access(file_path, F_OK) == -1) {
        return -1; // File does not exist
    }

    return send_file_to_browser(file_path);
}

int main() {
    ServerContext ctx = { .root_dir = "./" };

    Route routes[] = {
        { "/image.png", handle_image_request },
        { NULL, NULL }
    };

    const char *request_url = "/image.png";
    for (Route *r = routes; r->url != NULL; r++) {
        if (strcmp(r->url, request_url) == 0) {
            int result = r->handler(&ctx, request_url);
            if (result == -1) {
                printf("File not found.\n");
            }
            return 0;
        }
    }

    printf("Route not found.\n");
    return 1;
}