#include <stdio.h>
#include <string.h>
#include "uv.h"

typedef struct {
    uv_tcp_t server;
    uv_loop_t *loop;
} server_data;

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

void on_connection(uv_stream_t *server, int status) {
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server_data->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
        char response[256];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!");
        uv_buf_t buf = uv_buf_init(response, strlen(response));
        uv_write(req, (uv_stream_t*)client, &buf, 1, NULL);
    } else {
        uv_close((uv_handle_t*)client, free);
    }
}

void handle_request(uv_stream_t *server, int status) {
    char buffer[1024];
    uv_read_start(server, NULL, (uv_read_cb)on_connection);

    // Simplified parsing for demonstration
    if (fgets(buffer, sizeof(buffer), stdin)) {
        char product_code[50], quantity_str[50];
        sscanf(buffer, "GET /price?product_code=%[^&]&quantity=%s", product_code, quantity_str);
        int quantity = atoi(quantity_str);
        double price = get_price(product_code) * quantity;
        if (price >= 0) {
            char response[256];
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPrice: %.2f", price);
            write(server->io_watcher.fd, response, strlen(response));
        } else {
            char error_response[100] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code.";
            write(server->io_watcher.fd, error_response, strlen(error_response));
        }
    }

    uv_close((uv_handle_t*)server, NULL);
}

int main() {
    server_data data;
    data.loop = uv_default_loop();
    uv_tcp_init(data.loop, &data.server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3000, &addr);
    uv_listen((uv_stream_t*)&data.server, 128, on_connection);

    printf("Server running on port 3000\n");
    return uv_run(data.loop, UV_RUN_DEFAULT);
}
