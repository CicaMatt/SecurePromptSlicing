#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"

#define PORT 5000

double get_price(const char *product) {
    if (strcmp(product, "apple") == 0) return 1.2;
    if (strcmp(product, "banana") == 0) return 0.7;
    return -1; // Unknown product
}

void on_connection(uv_stream_t *server, int status) {
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL);
        char response[256];
        double price = get_price("apple"); // Default product
        int quantity = 1; // Default quantity

        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPrice for %d apples: %.2f", quantity, price * quantity);
        uv_write_t *req = (uv_write_t*) malloc(sizeof(uv_write_t));
        uv_buf_t buf = uv_buf_init(response, strlen(response));
        uv_write(req, (uv_stream_t*)client, &buf, 1, NULL);
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
    uv_listen((uv_stream_t*)&server, 128, on_connection);

    printf("Listening on port %d\n", PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}