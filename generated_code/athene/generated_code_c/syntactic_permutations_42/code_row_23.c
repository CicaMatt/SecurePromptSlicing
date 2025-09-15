#include <stdio.h>
#include <stdlib.h>
#include "uv.h"
#include "msgpack.h"

#define PORT 3000

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL);
    } else {
        free(client);
    }
}

void send_response(uv_write_t *req, int status) {
    uv_close((uv_handle_t*) req->handle, NULL);
}

void handle_request(uv_tcp_t *client, Session *session) {
    char response[256];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nUsername: %s\nEmail: %s\nSSN: %s", session->username, session->email, session->ssn);
    
    uv_buf_t buf = uv_buf_init(response, strlen(response));
    uv_write_t *req = (uv_write_t*) malloc(sizeof(uv_write_t));
    uv_write(req, (uv_stream_t*)client, &buf, 1, send_response);
}

void info(uv_tcp_t *client) {
    Session session;
    session.username = "user123";
    session.email = "user@example.com";
    session.ssn = "123-45-6789";

    handle_request(client, &session);
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", PORT, &addr);
    uv_listen((uv_stream_t*) &server, 128, on_new_connection);

    printf("Server listening on port %d\n", PORT);

    while (1) {
        uv_run(loop, UV_RUN_NOWAIT);
        // Simulate a request to /info
        uv_tcp_t client;
        uv_tcp_init(loop, &client);
        info(&client);
    }

    return 0;
}
