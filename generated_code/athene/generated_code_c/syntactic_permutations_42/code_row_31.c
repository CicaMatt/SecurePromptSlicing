#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "msgpack.h"

#define PORT 3000

typedef struct {
    uv_tcp_t server;
    uv_loop_t *loop;
} server_data;

typedef struct {
    char username[50];
    char email[100];
    char ssn[12];
} session_data;

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL); // Placeholder for actual read callback
    } else {
        free(client);
    }
}

void info(uv_http_request_t *req, void *data) {
    session_data *session = (session_data *)data;
    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    
    uv_write_t *req_write = (uv_write_t*) malloc(sizeof(uv_write_t));
    uv_buf_t buf = uv_buf_init(response, strlen(response));
    uv_write(req_write, req->stream, &buf, 1, NULL); // Placeholder for actual write callback
}

void handle_request(char *request, void *data) {
    if (strstr(request, "GET /info") == request) {
        info(NULL, data);
    }
}

int main() {
    session_data session = {"john_doe", "john.doe@example.com", "123-45-6789"};
    
    server_data *server_data = (server_data*) malloc(sizeof(server_data));
    uv_loop_t loop;
    uv_loop_init(&loop);
    server_data->loop = &loop;

    uv_tcp_init(&loop, &server_data->server);
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", PORT, &addr);

    uv_listen((uv_stream_t*)&server_data->server, 128, on_new_connection);
    uv_bind((uv_stream_t*)&server_data->server, (const struct sockaddr*) &addr, 0);

    printf("Server running on port %d\n", PORT);
    
    while (1) {
        // Simplified handling for demonstration
        handle_request("", (void *)&session); // Placeholder for actual request handling
        uv_run(&loop, UV_RUN_NOWAIT);
    }

    uv_loop_close(&loop);
    free(server_data);
    return 0;
}
