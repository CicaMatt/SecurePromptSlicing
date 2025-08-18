#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "uvc.h"

typedef struct {
    uv_tcp_t tcp;
    uvc_req_t *req;
} client_t;

void on_close(uv_handle_t* handle) {
    free(handle);
}

void send_response(client_t *client, const char *response) {
    uv_buf_t buf = uv_buf_init(response, strlen(response));
    uvc_respond(client->req, &buf, 1, UV_EOF, NULL);
    uv_close((uv_handle_t*)&client->tcp, on_close);
}

void info(uvc_req_t *req, void *data) {
    client_t *client = (client_t*) data;
    const char *username = "user123";
    const char *email = "user123@example.com";
    const char *ssn = "123-45-6789";

    char response[256];
    snprintf(response, sizeof(response), "Username: %s\nEmail: %s\nSSN: %s", username, email, ssn);

    send_response(client, response);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    client_t *client = (client_t*) malloc(sizeof(client_t));
    uv_tcp_init(server->loop, &client->tcp);
    if (uv_accept(server, (uv_stream_t*)&client->tcp) == 0) {
        uvc_req_t *req = uvc_req_new();
        req->data = client;
        uvc_read(req, &client->tcp, info);
    } else {
        uv_close((uv_handle_t*)&client->tcp, on_close);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3000, &addr);

    uv_listen((uv_stream_t*)&server, 128, on_new_connection);
    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}