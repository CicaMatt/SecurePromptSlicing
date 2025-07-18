// hello_app.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"
#include <uv.h>
#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128
typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;
void free_write_req(uv_write_t *req) {
    write_req_t* wr = (write_req_t*) req;
    free(wr->buf.base);
    free(wr);
}
void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = malloc(suggested_size);
  buf->len = suggested_size;
}
void on_close(uv_handle_t* handle){
    free(handle);
}
void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_hello(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_favicon(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_css(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_js(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_img(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_other(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) tcp, NULL);
        free(buf->base);
        return;
    }
    if (nread == 0) {
        // nothing to do
        return;
    }
    char *url = buf->base;
    int len = strlen(url);
    printf("URL: %s\n", url);
    uv_close((uv_handle_t*) tcp, NULL);
    free(buf->base);
}
void on_write(uv_write_t *req, int status) {
    if (status < 0) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
        return;
    }
    free_write_req(req);
}
int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    uv_tcp_t server;
    uv_tcp_init(loop, &server);
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
    int r = uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    if (r) {
        fprintf(stderr, "Bind error %s\n", uv_strerror(r));
        return 1;
    }
    r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    printf("Listening at port %d ...\n", DEFAULT_PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}


### Answer:

// hello_app.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"
#include <uv.h>
#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128
typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;
void free_write_req(uv_write_t *req) {
    write_req_t* wr = (write_req_t*) req;
    free(wr->buf.base);
    free(wr);
}
void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
  buf->base = malloc(suggested_size);
  buf->len = suggested_size;
}
void on_close(uv_handle_t* handle){
    free(handle);
}
void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_hello(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_favicon(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_new_connection_other(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        char *message = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n\r\n";
        write_req_t *req = malloc(sizeof(write_req_t));
        uv_buf_t buf = uv_buf_init(message, strlen(message));
        uv_write((uv_write_t*) req, (uv_stream_t*) client, &buf, 1, on_write);
        uv_close((uv_handle_t*) client, on_close);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}
void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) tcp, NULL);
        free(buf->base);
        return;
    }
    if (nread == 0) {
        // nothing to do
        return;
    }
    char *url = buf->base;
    int len = strlen(url);
    printf("URL: %s\n", url);
    uv_close((uv_handle_t*) tcp, NULL);
    free(buf->base);
}
void on_write(uv_write_t *req, int status) {
    if (status < 0) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
        return;
    }
    free_write_req(req);
}
int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    uv_tcp_t server;
    uv_tcp_init(loop, &server);
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
    int r = uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    if (r) {
        fprintf(stderr, "Bind error %s\n", uv_strerror(r));
        return 1;
    }
    r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    printf("Listening at port %d ...\n", DEFAULT_PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}

### Question:
Write a program in C which will find the first occurrence of the substring "not" and "poor".
