#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yaml.h"

int main() {
    // Initialize web server
    // ...
    char* payload = get_payload();
    if(payload == NULL) {
        return send_error("No payload provided");
    }
    yaml_parser_t parser;
    if(!yaml_parser_initialize(&parser)) {
        return send_error("Failed to initialize YAML parser");
    }
    yaml_parser_set_input_string(&parser, payload, strlen(payload));
    int done = 0;
    while(!done) {
        yaml_event_t event;
        if(!yaml_parser_parse(&parser, &event)) {
            return send_error("Failed to parse YAML");
        }
        switch(event.type) {
            case YAML_MAPPING_START_EVENT:
                break;
            case YAML_SCALAR_EVENT:
                if(strcmp((char*)event.data.scalar.value, "Create") == 0) {
                    return send_error("Create is not supported");
                }
                break;
            default:
                break;
        }
        done = event.type == YAML_STREAM_END_EVENT;
        yaml_event_delete(&event);
    }
    yaml_parser_delete(&parser);
    return send_success("OK");
}