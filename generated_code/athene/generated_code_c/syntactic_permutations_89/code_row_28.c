#include <stdio.h>
#include <stdlib.h>
#include "uv.h"

#define PORT 3000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Invalid product code
}

void on_read(uv_stream_t *server, ssize_t nread, const uv_buf_t *buf) {
    if (nread < 0) {
        if (nread != UV_EOF) fprintf(stderr, "Read error %s\n", uv_strerror(nread));
        uv_close((uv_handle_t*)server, NULL);
        free(buf->base);
        return;
    }

    char *request = buf->base;
    double price = -1;
    int quantity = 0;

    if (sscanf(request, "GET /price?product=%s&quantity=%d HTTP/1.1", &product_code[5], &quantity) == 2) {
        price = get_price(&product_code[9]);
    }

    char response[256];
    if (price > 0) {
        double total = price * quantity;
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f", total);
    } else {
        snprintf(response, sizeof(response), "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code");
    }

    uv_write_t *req = malloc(sizeof(uv_write_t));
    uv_buf_t wrbuf = uv_buf_init(response, strlen(response));

    uv_write(req, (uv_stream_t*)server, &wrbuf, 1, NULL);
    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, [](uv_handle_t*, size_t suggested_size, uv_buf_t* buf) {
            *buf = uv_buf_init((char*)malloc(suggested_size), suggested_size);
        }, on_read);
    } else {
        uv_close((uv_handle_t*)client, free);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", PORT, &addr);
    uv_listen((uv_stream_t*)&server, 128, on_new_connection);

    printf("Server listening on port %d\n", PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}