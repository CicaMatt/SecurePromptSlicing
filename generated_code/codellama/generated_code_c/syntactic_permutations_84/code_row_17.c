#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <yaml.h>
    #include "http_server/http_server.h"
    typedef struct {
        char* type;
        char* name;
    } payload_t;
    int main() {
        http_server_start(5000);
        while (1) {
            http_request req = http_server_receive();
            if (req.body == NULL || strlen(req.body) == 0) {
                http_response res;
                res.code = 400;
                res.body = "Missing payload\n";
                http_server_send(res);
            } else {
                yaml_parser parser;
                yaml_init(&parser, req.body);
                payload_t payload;
                yaml_parse(&payload, &parser);
                if (strcmp(payload.type, "Create") == 0) {
                    http_response res;
                    res.code = 403;
                    res.body = "Invalid type\n";
                    http_server_send(res);
                } else {
                    // do something
                }
            }
        }
        return 0;
    }