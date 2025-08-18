#include <stdio.h>
#include <string.h>
#include "uv.h"

#define PORT 5000

typedef struct {
    const char *code;
    double price;
} Product;

Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 15.50}
};

double get_price(const char *product_code) {
    for (int i = 0; i < sizeof(products)/sizeof(Product); i++) {
        if (strcmp(product_code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

void on_new_connection(uv_stream_t *server, int status) {
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL);
        char response[1024];
        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nProduct not found");
        
        char buffer[1024];
        int nread;
        uv_read_start((uv_stream_t*)client, NULL, (uv_read_cb) &on_read);

        void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t* buf) {
            if (nread < 0) {
                free(client);
                return;
            }
            sscanf(buf->base, "GET /price?code=%s&quantity=%d HTTP/1.1", buffer, &nread);

            double price = get_price(buffer);
            int quantity = nread;

            if (price >= 0.0) {
                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nTotal Price: %.2f", price * quantity);
            }

            uv_write_t req;
            uv_buf_t wrbuf = uv_buf_init(response, strlen(response));
            uv_write(&req, (uv_stream_t*)client, &wrbuf, 1, NULL);

            free(client);
        }
    } else {
        free(client);
    }
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", PORT, &addr);
    uv_listen((uv_stream_t*)&server, 128, on_new_connection);

    printf("Server running on port %d\n", PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}