#include <arpa/inet.h>
#include <ctype.h>
#include <err.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <yaml.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_request(evhttp_request *req, void *arg) {
    struct evbuffer *evb;
    const char *uri = evhttp_request_get_uri(req);
    const char *method = evhttp_request_get_command(req);

    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0) {
        evhttp_send_error(req, HTTP_BADREQUEST, 0, "Unsupported method");
        return;
    }

    struct evkeyvalq params;
    evhttp_parse_query(evhttp_request_get_input_buffer(req), &params);

    if (evhttp_find_header(&params, "payload") == NULL) {
        char *response = "Payload parameter is missing";
        evb = evbuffer_new();
        evbuffer_add_printf(evb, "%s", response);
        evhttp_send_reply(req, HTTP_OK, "OK", evb);
        evbuffer_free(evb);
    } else {
        struct evkeyval *pair;
        pair = evhttp_find_header(&params, "payload");
        
        yaml_parser_t parser;
        if (!yaml_parser_initialize(&parser)) errx(1, "Failed to initialize YAML parser");

        yaml_event_t event;
        char *stream = strdup(pair->value);
        size_t len = strlen(stream);

        if (!yaml_parser_set_input_string(&parser, stream, len))
            errx(1, "Failed to set input string for YAML parser");

        int done = 0;
        while (!done) {
            if (!yaml_parser_parse(&parser, &event))
                errx(1, "YAML parse error %d", event.error);

            if (event.type == YAML_SCALAR_EVENT && !strcmp((char *)event.data.scalar.value, "Create")) {
                char *response = "Error: Type is Create";
                evb = evbuffer_new();
                evbuffer_add_printf(evb, "%s", response);
                evhttp_send_reply(req, HTTP_BADREQUEST, "Bad Request", evb);
                evbuffer_free(evb);
                done = 1;
            }

            if (event.type == YAML_STREAM_END_EVENT) {
                done = 1;
            }
            yaml_event_delete(&event);
        }
        yaml_parser_delete(&parser);
        free(stream);

        char *response = "Payload processed successfully";
        evb = evbuffer_new();
        evbuffer_add_printf(evb, "%s", response);
        evhttp_send_reply(req, HTTP_OK, "OK", evb);
        evbuffer_free(evb);
    }
    
    evhttp_clear_headers(&params);
}

int main(int argc, char **argv) {
    struct event_base *base;
    struct evhttp *http;
    struct evhttp_bound_socket *handle;

    base = event_base_new();
    if (!base)
        errx(1, "Couldn't create an event_base: %s", strerror(errno));

    http = evhttp_new(base);
    if (!http)
        errx(1, "couldn't create evhttp. Out of memory");

    evhttp_set_gencb(http, handle_request, NULL);

    handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", 5000);
    if (!handle)
        errx(1, "couldn't bind to port 5000");
    
    event_base_dispatch(base);

    evhttp_free(http);
    event_base_free(base);

    return 0;
}