#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "msgpack.h"

typedef struct {
    uv_loop_t *loop;
    uv_tcp_t server;
} app_t;

void on_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "Failed to establish connection: %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, NULL, NULL); // Placeholder for actual read callback
    } else {
        free(client);
    }
}

void on_request(uv_work_t *req) {
    char *payload = "name=John Doe"; // Example payload from URL
    msgpack_unpacked result;
    msgpack_unpacked_init(&result);

    msgpack_object_kv kv_name = {"name", {MSGPACK_OBJECT_STR, {"", 0}}};
    if (msgpack_unpack(payload, strlen(payload), NULL, &result) == 1 && result.data.type == MSGPACK_OBJECT_MAP) {
        for (size_t i = 0; i < result.data.via.map.size; i++) {
            msgpack_object_kv kv = result.data.via.map.ptr[i];
            if (strcmp(kv.key.via.str.ptr, "name") == 0) {
                kv_name = kv;
                break;
            }
        }
    }

    printf("Name: %.*s\n", (int)kv_name.val.via.str.size, kv_name.val.via.str.ptr);

    msgpack_unpacked_destroy(&result);
}

void on_close(uv_handle_t *handle) {
    free(handle);
}

int main() {
    app_t app;
    uv_loop_init(app.loop = malloc(sizeof(uv_loop_t)));

    uv_tcp_init(app.loop, &app.server);
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 3000, &addr);

    uv_bind(&app.server, (const struct sockaddr*)&addr, UV_TCP_IPV6ONLY);
    uv_listen((uv_stream_t*)&app.server, 128, on_connection);

    uv_work_t req;
    uv_queue_work(app.loop, &req, on_request, NULL);

    printf("Server running at http://localhost:3000/api\n");

    uv_run(app.loop, UV_RUN_DEFAULT);
    uv_loop_close(app.loop);
    free(app.loop);

    return 0;
}


Note: This code is a simplified version and does not include the full implementation of parsing URL parameters or handling HTTP requests. It assumes a fixed payload for demonstration purposes. For a real web application, you would need to use an HTTP server library like libuv-http or similar to handle HTTP requests properly.