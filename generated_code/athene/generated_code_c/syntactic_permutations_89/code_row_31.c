#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"

typedef struct {
    uv_tcp_t server;
    uv_timer_t timer;
} app_ctx;

double get_price(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Invalid product code
}

void on_new_connection(uv_stream_t* server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, uv_alloc_cb(0), uv_read_cb(0));
    } else {
        free(client);
    }
}

void on_read(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*)stream, NULL);
        free(buf->base);
        return;
    }

    char* query = strstr(buf->base, "?product=");
    if (query) {
        char product_code[10];
        int quantity = 0;
        sscanf(query + 8, "%[^&]&quantity=%d", product_code, &quantity);
        double price = get_price(product_code);
        if (price >= 0) {
            char response[256];
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: %zu\r\n\r\n%.2f", strlen("%.2f"), price * quantity);
            uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
            uv_buf_t wrbuf = uv_buf_init(response, strlen(response));
            uv_write(req, stream, &wrbuf, 1, NULL);
        } else {
            char response[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nInvalid product code";
            uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
            uv_buf_t wrbuf = uv_buf_init(response, sizeof(response) - 1);
            uv_write(req, stream, &wrbuf, 1, NULL);
        }
    } else {
        char response[] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\nContent-Length: 26\r\n\r\nInvalid request format or missing parameters";
        uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
        uv_buf_t wrbuf = uv_buf_init(response, sizeof(response) - 1);
        uv_write(req, stream, &wrbuf, 1, NULL);
    }

    free(buf->base);
}

void start_server(app_ctx* app) {
    uv_ip4_addr("0.0.0.0", 8080, (struct sockaddr_in*)&app->server.addr);
    uv_tcp_init(app->timer.loop, &app->server);
    if (uv_listen((uv_stream_t*)&app->server, 128, on_new_connection) == 0) {
        printf("Server listening on port 8080\n");
    } else {
        fprintf(stderr, "Listen error %s\n", uv_strerror(uv_last_error(app->timer.loop)));
    }
}

int main() {
    app_ctx app;
    uv_loop_t* loop = uv_default_loop();

    start_server(&app);

    return uv_run(loop, UV_RUN_DEFAULT);
}