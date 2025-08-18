#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "http_parser.h"

#define PORT 3000

typedef struct {
    uv_tcp_t server;
    uv_loop_t *loop;
} server_data;

typedef struct {
    char username[100];
    char email[100];
    char ssn[12];
} session;

session current_session = {"user1", "user1@example.com", "123-45-6789"};

void info(uv_write_t *req, int status) {
    uv_buf_t buf;
    asprintf((char**)&buf.base, 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: text/plain\r\n"
             "Content-Length: %zu\r\n"
             "\r\n"
             "Username: %s\n"
             "Email: %s\n"
             "SSN: %s\n",
             strlen(current_session.username) + strlen(current_session.email) + strlen(current_session.ssn) + 21,
             current_session.username, current_session.email, current_session.ssn);
    buf.len = strlen(buf.base);

    uv_write_t *write_req = (uv_write_t*)malloc(sizeof(uv_write_t));
    uv_buf_t data = uv_buf_init(buf.base, buf.len);
    uv_write(write_req, req->handle, &data, 1, NULL);
}

void on_new_connection(uv_stream_t* server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, info);
    } else {
        free(client);
    }
}

int main() {
    server_data data;
    data.loop = uv_default_loop();

    uv_tcp_init(data.loop, &data.server);
    struct sockaddr_in bind_addr = uv_ip4_addr("0.0.0.0", PORT);

    uv_listen((uv_stream_t*)&data.server, 128, on_new_connection);

    printf("Server running on port %d\n", PORT);
    return uv_run(data.loop, UV_RUN_DEFAULT);
}