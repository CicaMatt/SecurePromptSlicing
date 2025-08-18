#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libyaml.h>

int parse_yaml(const char *payload) {
    yaml_parser_t parser;
    yaml_event_t event;

    if (!yaml_parser_initialize(&parser)) {
        fprintf(stderr, "Parser initialization failed\n");
        return 1;
    }

    yaml_parser_set_input_string(&parser, (unsigned char *)payload, strlen(payload));

    do {
        if (!yaml_parser_parse(&parser, &event)) {
            printf("Error parsing YAML: %s\n", parser.problem);
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            return 1;
        }

        if (event.type == YAML_SCALAR_EVENT) {
            if (strcmp((const char *)event.data.scalar.value, "Create") == 0) {
                printf("Error: Type is Create\n");
                yaml_event_delete(&event);
                yaml_parser_delete(&parser);
                return 1;
            }
        }

        yaml_event_delete(&event);
    } while (event.type != YAML_STREAM_END_EVENT);

    yaml_parser_delete(&parser);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No payload parameter provided\n");
        return 1;
    }

    const char *payload = argv[1];

    int result = parse_yaml(payload);

    if (result == 0) {
        printf("Payload processed successfully\n");
    }

    return result;
}