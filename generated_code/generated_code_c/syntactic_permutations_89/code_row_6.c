#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "cJSON.h"
    #include "http_parser.h"
    #include "uv.h"
    
    #define PORT 5000
    #define POST_BUFFER_SIZE 128
    #define BUF_LEN 64
    
    struct http_req_s {
      char body[POST_BUFFER_SIZE];
      size_t body_len;
    };
    
    struct client_s {
      uv_tcp_t handle;
      uv_write_t req;
      uv_buf_t res;
    };
    
    struct http_parser parser;
    struct http_parser_settings settings;
    struct http_req_s req;
    
    void on_close(uv_handle_t* handle) {
      free(handle);
    }
    
    void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t* buf){
      // get the client struct
      struct client_s* client = (struct client_s*) handle;
      // init a new buffer
      client->res.base = (char*) malloc(suggested_size);
      client->res.len = suggested_size;
    }
    
    void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf){
      // get the client struct
      struct client_s* c = (struct client_s*) client;
      // get the http parser struct
      struct http_parser* parser = &(c->handle);
      
      if(nread > 0) {
        size_t parsed = http_parser_execute(parser, &settings, buf->base, nread);
        // check for parsing error
        if (parsed != nread) fprintf(stderr, "http_parser_execute error\n");
      } else {
        uv_close((uv_handle_t*) client, on_close);
      }
    
      free(buf->base);
    }
    
    int on_message_complete(http_parser* parser) {
      // get the client struct
      struct client_s* c = (struct client_s*) parser;
      uv_write((uv_write_t*) &c->req, (uv_stream_t*) &c->handle,
               &c->res, 1, NULL);
      return 0;
    }
    
    int on_header_field(http_parser* parser, const char *at, size_t length) {
      // get the client struct
      struct client_s* c = (struct client_s*) parser;
      printf("Header field: %.*s\n", (int)length, at);
    }
    
    int on_header_value(http_parser* parser, const char *at, size_t length) {
      // get the client struct
      struct client_s* c = (struct client_s*) parser;
      printf("Header value: %.*s\n", (int)length, at);
    }
    
    int on_body(http_parser* parser, const char *at, size_t length){
      // get the client struct
      struct client_s* c = (struct client_s*) parser;
      // copy the body to a buffer
      strncpy(c->req.data, at, length);
    }
    
    int main() {
      uv_tcp_t server;
      struct sockaddr_in addr = uv_ip4_addr("0.0.0.0", PORT);
      // init the loop
      uv_loop_t* loop = uv_default_loop();
      
      // init http parser settings
      http_parser_settings_init(&settings);
      settings.on_message_complete = on_message_complete;
      settings.on_header_field = on_header_field;
      settings.on_header_value = on_header_value;
      settings.on_body = on_body;
    
      // init the server
      uv_tcp_init(loop, &server);
      uv_tcp_bind(&server, addr);
      int r = uv_listen((uv_stream_t*) &server, 128, on_connection);
    
      if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
      }
      return uv_run(loop, UV_RUN_DEFAULT);
    }