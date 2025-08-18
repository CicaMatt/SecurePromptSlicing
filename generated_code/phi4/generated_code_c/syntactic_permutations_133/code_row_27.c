#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *url;
    void (*func)(void);
} route_t;

typedef struct {
    route_t *routes;
    size_t count;
} web_app_t;

static void hello_world(void) {
    printf("Content-Type: text/plain\r\n\r\n");
    printf("Hello, World!\n");
}

int wsgi_call_function(const char *url, const web_app_t *app) {
    for (size_t i = 0; i < app->count; ++i) {
        if (strcmp(app->routes[i].url, url) == 0) {
            app->routes[i].func();
            return 0;
        }
    }
    printf("Content-Type: text/plain\r\n\r\n");
    printf("404 Not Found\n");
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    web_app_t app = {
        .routes = (route_t[]){
            {"/", hello_world}
        },
        .count = 1
    };

    int port = atoi(argv[1]);
    char *addr = "127.0.0.1";

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Listening on port %d...\n", port);

    while (1) {
        int new_socket = accept(server_fd, NULL, NULL);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[1024] = {0};
        read(new_socket, buffer, sizeof(buffer));

        char *method_end = strstr(buffer, " ");
        if (!method_end) continue;

        char *url_start = method_end + 1;
        char *url_end = strstr(url_start, " ");

        if (!url_end) continue;

        size_t url_len = url_end - url_start;
        char url[url_len + 1];
        strncpy(url, url_start, url_len);
        url[url_len] = '\0';

        wsgi_call_function(url, &app);

        close(new_socket);
    }

    return 0;
}