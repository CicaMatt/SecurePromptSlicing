#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "uv.h"

    static uv_loop_t* loop;

    void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
        *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
    }

    void on_read(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
        if (nread < 0) {
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
            uv_close((uv_handle_t*) client, NULL);
            free(buf->base);
            return;
        }

        char* file = "/images/";
        char* url = "http://example.com";

        if (strstr(buf->base, url) != NULL) {
            strcat(file, buf->base + strlen(url));
            FILE* fp = fopen(file, "r");

            if (fp != NULL) {
                char* file_contents;
                long input_file_size;
                size_t result;

                fseek(fp , 0 , SEEK_END);
                input_file_size = ftell(fp);
                rewind(fp);

                file_contents = (char*) malloc(input_file_size * (sizeof(char)));

                result = fread(file_contents, sizeof(char), input_file_size, fp);

                if (result != input_file_size) {
                    fputs("Reading error", stderr);
                }

                uv_buf_t resp = uv_buf_init(file_contents, strlen(file_contents));
                uv_write_t req;
                uv_write((uv_write_t*) &req, client, &resp, 1, NULL);

                free(file_contents);
            }
        } else {
            char* resp = "404 Not Found";
            uv_buf_t buf = uv_buf_init(resp, strlen(resp));
            uv_write_t req;
            uv_write((uv_write_t*) &req, client, &buf, 1, NULL);
        }
    }

    void on_new_connection(uv_stream_t* server, int status) {
        if (status < 0) {
            fprintf(stderr, "New connection error %s\n", uv_strerror(status));
            return;
        }

        uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
        uv_tcp_init(loop, client);

        if (uv_accept(server, (uv_stream_t*) client) == 0) {
            uv_read_start((uv_stream_t*) client, alloc_buffer, on_read);
        }
    }

    int main() {
        loop = uv_default_loop();

        struct sockaddr_in bind_addr;
        uv_tcp_t server;

        uv_tcp_init(loop, &server);
        uv_ip4_addr("0.0.0.0", 7000, &bind_addr);

        uv_tcp_bind(&server, (const struct sockaddr*) &bind_addr, 0);
        int r = uv_listen((uv_stream_t*) &server, SOMAXCONN, on_new_connection);

        if (r) {
            fprintf(stderr, "Listen error %s\n", uv_strerror(r));
            return 1;
        }

        return uv_run(loop, UV_RUN_DEFAULT);
    }