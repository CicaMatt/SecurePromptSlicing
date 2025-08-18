#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"

#define ASSERT(r) if ((r) < 0) { fprintf(stderr, "%s\n", uv_strerror(r)); exit(1); }

typedef struct {
    char code[20];
    double price;
} Product;

Product products[] = {
    {"A123", 9.99},
    {"B456", 19.99},
    {"C789", 29.99}
};

double get_product_price(const char *code) {
    for (int i = 0; i < sizeof(products) / sizeof(Product); i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

void on_connection(uv_stream_t* server, int status) {
    uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    ASSERT(uv_tcp_init(server->loop, client));

    if (status == 0) {
        ASSERT(uv_accept(server, (uv_stream_t*)client));
        char buffer[256];
        uv_read_start((uv_stream_t*)client, NULL, (uv_read_cb)(void*)buffer);
    } else {
        free(client);
    }
}

void on_read(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*)stream, NULL);
        return;
    }

    char *request = malloc(nread + 1);
    memcpy(request, buf->base, nread);
    request[nread] = '\0';

    char code[20];
    int quantity;
    sscanf(request, "GET /price?code=%[^&]&quantity=%d", code, &quantity);

    double price = get_product_price(code) * quantity;

    char response[1024];
    if (price >= 0.0) {
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%.2f", price);
    } else {
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nProduct not found");
    }

    uv_write_t* write_req = (uv_write_t*) malloc(sizeof(uv_write_t));
    uv_buf_t buf2 = uv_buf_init(response, strlen(response));
    ASSERT(uv_write(write_req, stream, &buf2, 1, NULL));

    free(request);
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 8080, &addr);
    ASSERT(uv_listen((uv_stream_t*)&server, 128, on_connection));

    printf("Server running on port 8080\n");

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}