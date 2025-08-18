#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "msgpack.h"

#define CHECK(x) if (!(x)) { fprintf(stderr, "Error: %s\n", uv_strerror(uv_last_error(uv_default_loop()))); exit(1); }

typedef struct {
    char username[100];
    char email[100];
    char ssn[12];
} Session;

void on_read(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        if (nread != UV_EOF) fprintf(stderr, "Read error %s\n", uv_strerror(nread));
        uv_close((uv_handle_t*)client, NULL);
        free(buf->base);
        return;
    }

    Session session = { .username = "user123", .email = "user123@example.com", .ssn = "123-45-6789" };
    
    char response[256];
    snprintf(response, sizeof(response), 
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: application/json\r\n"
             "Content-Length: %lu\r\n"
             "\r\n"
             "{\"username\": \"%s\", \"email\": \"%s\", \"ssn\": \"%s\"}",
             (unsigned long)(strlen(session.username) + strlen(session.email) + strlen(session.ssn) + 38),
             session.username, session.email, session.ssn);

    uv_write_t* req = (uv_write_t*)malloc(sizeof(uv_write_t));
    uv_buf_t wrbuf = uv_buf_init(response, strlen(response));

    CHECK(uv_write(req, (uv_stream_t*)client, &wrbuf, 1, NULL) == 0);
}

void on_new_connection(uv_stream_t* server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);
    CHECK(uv_accept(server, (uv_stream_t*)client) == 0);

    uv_read_start((uv_stream_t*)client, [](uv_handle_t*, size_t suggested_size, uv_buf_t* buf) {
        *buf = uv_buf_init((char*)malloc(suggested_size), suggested_size);
    }, on_read);
}

int main() {
    uv_tcp_t server;
    uv_loop_t* loop = uv_default_loop();

    CHECK(uv_tcp_init(loop, &server) == 0);

    struct sockaddr_in addr;
    CHECK(uv_ip4_addr("0.0.0.0", 8080, &addr) == 0);
    CHECK(uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0) == 0);
    int r = uv_listen((uv_stream_t*)&server, 128, on_new_connection);

    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }

    printf("Server running on port 8080\n");
    CHECK(uv_run(loop, UV_RUN_DEFAULT) == 0);

    return 0;
}