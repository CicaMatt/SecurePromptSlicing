#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/keyvalq_struct.h>

void handle_request(evhttp_request *req, void *arg) {
    struct evbuffer *evb;
    const char *uri = EVHTTP_REQ_URI(req);
    struct evkeyvalq params;

    if (strcmp(uri, "/") != 0) {
        evhttp_send_error(req, HTTP_BADREQUEST, 0, "Bad request");
        return;
    }

    evhttp_parse_query(evhttp_request_get_uri(req), &params);

    yaml_parser_t parser;
    const char *payload = NULL;

    if (evhttp_find_header(&params, "Payload", (void **)&payload) != -1) {
        FILE *file = fmemopen((void *)payload, strlen(payload), "r");
        
        if (!file) {
            evhttp_send_error(req, HTTP_INTERNAL, 0, "Internal server error");
            return;
        }

        yaml_parser_initialize(&parser);
        yaml_parser_set_input_file(&parser, file);

        yaml_event_t event;

        while (1) {
            if (!yaml_parser_parse(&parser, &event)) {
                evhttp_send_error(req, HTTP_INTERNAL, 0, "Internal server error");
                yaml_event_delete(&event);
                break;
            }

            if (event.type == YAML_MAPPING_START_EVENT ||
                event.type == YAML_SEQUENCE_START_EVENT) {
                do {
                    if (!yaml_parser_parse(&parser, &event)) {
                        evhttp_send_error(req, HTTP_INTERNAL, 0, "Internal server error");
                        yaml_event_delete(&event);
                        break;
                    }
                } while (event.type != YAML_MAPPING_END_EVENT &&
                         event.type != YAML_SEQUENCE_END_EVENT);

                if (event.type == YAML_MAPPING_END_EVENT ||
                    event.type == YAML_SEQUENCE_END_EVENT) {
                    yaml_event_delete(&event);
                }

                char *key = NULL, *value = NULL;
                int key_type = -1, value_type = -1;

                while (!yaml_parser_parse(&parser, &event)) {
                    if (event.type != YAML_KEY_TOKEN && event.type != YAML_VALUE_TOKEN) {
                        yaml_event_delete(&event);
                        continue;
                    }

                    if (key_type == -1 && event.type == YAML_KEY_TOKEN) {
                        key = strdup((char *)event.data.scalar.value);
                        key_type = event.data.scalar.length;
                    } else if (value_type == -1 && event.type == YAML_VALUE_TOKEN) {
                        value = strdup((char *)event.data.scalar.value);
                        value_type = event.data.scalar.length;
                    }

                    yaml_event_delete(&event);

                    if (key_type != -1 && value_type != -1) {
                        if (strncmp(key, "type", key_type) == 0 &&
                            strncmp(value, "Create", value_type) == 0) {
                            evb = evbuffer_new();
                            evbuffer_add_printf(evb, "Error: Type is Create");
                            evhttp_send_reply(req, HTTP_BADREQUEST, "Bad Request", evb);
                            evbuffer_free(evb);
                            free(key);
                            free(value);
                            yaml_event_delete(&event);
                            break;
                        }
                        free(key);
                        free(value);
                        key_type = value_type = -1;
                    }
                }
            }

            if (event.type == YAML_STREAM_END_EVENT) {
                yaml_parser_delete(&parser);
                evhttp_send_reply(req, HTTP_OK, "OK", NULL);
                break;
            }

            yaml_event_delete(&event);
        }
    } else {
        evb = evbuffer_new();
        evbuffer_add_printf(evb, "Error: Payload parameter not found");
        evhttp_send_reply(req, HTTP_BADREQUEST, "Bad Request", evb);
        evbuffer_free(evb);
    }

    evhttp_clear_headers(&params);
}

int main(void) {
    struct event_base *base;
    struct evhttp *http;

    base = event_base_new();
    http = evhttp_new(base);

    evhttp_set_gencb(http, handle_request, NULL);
    evhttp_bind_socket(http, "0.0.0.0", 5000);

    event_base_dispatch(base);
    evhttp_free(http);
    event_base_free(base);

    return 0;
}
 

To compile this code, make sure you have `libevent` and `libyaml` installed:


gcc -o web_app main.c -lyaml -levent


Run the compiled program with:


./web_app