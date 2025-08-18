#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "msgpack.h"

typedef struct {
    uv_tcp_t server;
    uv_loop_t *loop;
} server_data;

typedef struct {
    char username[256];
    char email[256];
    char ssn[128];
} user_session;

user_session session = {"john_doe", "john@example.com", "123-45-6789"};

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "Failed to accept new connection: %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL); // Simplified for demo
    } else {
        free(client);
    }
}

void send_response(uv_tcp_t *client, const char *response) {
    uv_buf_t buf = uv_buf_init(response, strlen(response));
    uv_write_t *req = (uv_write_t*) malloc(sizeof(uv_write_t));
    uv_write(req, (uv_stream_t*)client, &buf, 1, NULL);
}

void info_request(uv_tcp_t *client) {
    char response[512];
    snprintf(response, sizeof(response), 
             "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n"
             "Username: %s\nEmail: %s\nSSN: %s",
             session.username, session.email, session.ssn);
    send_response(client, response);
}

void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        free(client);
        return;
    }

    if (buf && buf->base[0] == 'G' && buf->base[1] == 'E' && buf->base[2] == 'T') {
        info_request((uv_tcp_t*)client);
    } else {
        send_response((uv_tcp_t*)client, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNot Found");
    }

    free(client);
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    server_data data;
    data.loop = loop;

    uv_tcp_init(loop, &data.server);
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3000, &addr);

    uv_tcp_bind(&data.server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &data.server, 128, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }

    printf("Server running on port 3000\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}