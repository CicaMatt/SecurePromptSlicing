#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "http_parser.h"

void after_write(uv_write_t* req, int status);
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
void on_new_connection(uv_stream_t* server, int status);
void on_read(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf);
void on_close(uv_handle_t* peer);
int main() {
    // Initialize libuv.
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    // Create a server handle.
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in bind_addr;
    uv_ip4_addr("0.0.0.0", 7000, &bind_addr);
    uv_tcp_bind(&server, (const struct sockaddr*)&bind_addr, 0);

    int r = uv_listen((uv_stream_t*)&server, 128, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }

    printf("Listening at localhost:7000\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}
void on_new_connection(uv_stream_t* server, int status) {
    // Allocate a client structure to hold the new connection.
    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);

    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        // Start reading data from the client.
        uv_read_start((uv_stream_t*)client, alloc_buffer, on_read);
    } else {
        uv_close((uv_handle_t*)client, on_close);
    }
}
void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
    // Allocate a buffer for reading data from the client.
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}
void on_read(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
    // If there was a problem while reading the data, close the connection.
    if (nread < 0) {
        uv_close((uv_handle_t*)client, on_close);
        return;
    }

    // Process the received data.
    char* request = buf->base;
    char* response = malloc(1024 * sizeof(char));
    sprintf(response, "Hello, %s!", request);

    // Send the response back to the client.
    uv_write_t write_req;
    uv_buf_t response_buf = uv_buf_init(response, strlen(response));
    uv_write((uv_write_t*)&write_req, client, &response_buf, 1, after_write);
}
void after_write(uv_write_t* req, int status) {
    // Close the connection.
    uv_close((uv_handle_t*)req->handle, on_close);
}
void on_close(uv_handle_t* peer) {
    // Free the memory allocated for the client structure.
    free(peer);
}