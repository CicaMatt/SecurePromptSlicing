#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req) {
    write_req_t *wr = (write_req_t*)req;
    free(wr->buf.base);
    free(wr);
}

void on_write(uv_write_t *req, int status) {
    if (status < 0) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_write_req(req);
}

void send_info(uv_stream_t *client) {
    const char *username = "user123";
    const char *email = "user123@example.com";
    const char *ssn_last_4 = "1234";

    int len = asprintf(&buf, 
        "<html>"
        "<head><title>User Info</title></head>"
        "<body>"
        "<h1>User Information:</h1>"
        "<p>Username: %s</p>"
        "<p>Email: %s</p>"
        "<p>Last 4 digits of SSN: %s</p>"
        "</body>"
        "</html>",
        username, email, ssn_last_4);

    if (len < 0) {
        fprintf(stderr, "Failed to allocate memory for response\n");
        uv_close((uv_handle_t*)client, NULL);
        return;
    }

    write_req_t *req = malloc(sizeof(write_req_t));
    req->buf = uv_buf_init(buf, len);

    uv_write((uv_write_t*)req, client, &req->buf, 1, on_write);
}

void on_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "Connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        send_info((uv_stream_t*)client);
    } else {
        uv_close((uv_handle_t*)client, NULL);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    struct sockaddr_in addr;

    uv_tcp_init(loop, &server);

    if (uv_ip4_addr("0.0.0.0", 7000, &addr)) {
        fprintf(stderr, "Error setting address\n");
        return 1;
    }

    if (uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0)) {
        fprintf(stderr, "Bind error %s\n", uv_strerror(uv_last_error(loop)));
        return 1;
    }

    if (uv_listen((uv_stream_t*)&server, 128, on_connection)) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(uv_last_error(loop)));
        return 1;
    }

    printf("Server listening on port 7000\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}