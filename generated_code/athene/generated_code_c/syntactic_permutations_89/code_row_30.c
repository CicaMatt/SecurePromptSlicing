#include <stdio.h>
#include <stdlib.h>
#include "uv.h"

uv_loop_t *loop;
uv_tcp_t server;

double get_price_for_product(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "Connection failed\n");
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, on_client_read);
    } else {
        free(client);
    }
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}

void send_response(uv_stream_t *client, const char *response) {
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    uv_buf_t buf = uv_buf_init(response, strlen(response));

    uv_write(req, client, &buf, 1, free_on_complete);
}

void free_on_complete(uv_write_t *req, int status) {
    free(req->data);
    free(req);

    uv_close((uv_handle_t*) req->handle, free_on_close);
}

void free_on_close(uv_handle_t* handle) {
    free(handle);
}

void on_client_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf) {
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, free_on_close);
        return;
    }

    char *request = malloc(nread + 1);
    memcpy(request, buf->base, nread);
    request[nread] = '\0';

    char product_code[10];
    int quantity;
    if (sscanf(request, "GET /price?product=%9s&quantity=%d", product_code, &quantity) == 2) {
        double price_per_unit = get_price_for_product(product_code);
        if (price_per_unit >= 0) {
            char response[100];
            snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%.2f", price_per_unit * quantity);
            send_response(client, response);
        } else {
            send_response(client, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid product code");
        }
    } else {
        send_response(client, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request");
    }

    free(request);
}

int main() {
    loop = uv_default_loop();

    uv_ip4_addr("0.0.0.0", 8080, &server.addr);
    uv_tcp_init(loop, &server);

    int r;
    if ((r = uv_bind(&server, (const struct sockaddr*)&server.addr, UV_TCP_IPV6ONLY)) < 0) {
        fprintf(stderr, "Bind error %s\n", uv_strerror(r));
        return 1;
    }

    if ((r = uv_listen((uv_stream_t*) &server, 128, on_new_connection)) < 0) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }

    printf("Server running at http://localhost:8080/\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}