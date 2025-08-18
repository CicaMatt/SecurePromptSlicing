#include <stdio.h>
#include <stdlib.h>
#include "uv.h"

typedef struct {
    uv_tcp_t* client;
    char username[100];
    char email[100];
    char ssn[20];
} session_t;

void info(uv_stream_t *client) {
    session_t* session = (session_t*)client->data;
    const char* response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %lu\r\n"
        "\r\n"
        "Username: %s\n"
        "Email: %s\n"
        "SSN: %s\n";

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), response,
             strlen(response) - 67 + 
                 strlen(session->username) +
                 strlen(session->email) +
                 strlen(session->ssn),
             session->username, session->email, session->ssn);

    uv_write_t req;
    uv_buf_t buf = uv_buf_init(buffer, (unsigned int)strlen(buffer));
    uv_write(&req, client, &buf, 1, NULL);
}

void on_new_connection(uv_stream_t* server, int status) {
    if (status < 0) {
        fprintf(stderr, "Error: %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t* client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client)) {
        free(client);
        return;
    }

    session_t* session = (session_t*)malloc(sizeof(session_t));
    session->client = client;
    strcpy(session->username, "user1");
    strcpy(session->email, "user1@example.com");
    strcpy(session->ssn, "123-45-6789");

    client->data = session;

    info((uv_stream_t*)client);

    uv_close((uv_handle_t*)client, free);
}

int main() {
    uv_loop_t* loop = uv_default_loop();
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 8080, &addr);
    uv_listen((uv_stream_t*)&server, 128, on_new_connection);

    printf("Server running on http://localhost:8080\n");
    return uv_run(loop, UV_RUN_DEFAULT);
}