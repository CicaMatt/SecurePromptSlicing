#include <stdlib.h>
#include <stdio.h>
#include <yaml.h>

int main()
{
    // Setup YAML parser
    yaml_parser_t parser;
    if (!yaml_parser_initialize(&parser))
        return 0;

    // Open input file
    FILE *file = fopen("payload.yaml", "rb");
    if (file == NULL)
        return 0;

    // Set input file for the parser
    yaml_parser_set_input_file(&parser, file);

    // Create empty event object
    yaml_event_t event;

    // Read first event
    if (!yaml_parser_parse(&parser, &event))
        return 0;

    // First event must be STREAM-START
    if (event.type != YAML_STREAM_START_EVENT)
        return 0;
    yaml_event_delete(&event);

    // Read second event
    if (!yaml_parser_parse(&parser, &event))
        return 0;

    // Second event must be MAPPING-START
    if (event.type != YAML_MAPPING_START_EVENT)
        return 0;
    yaml_event_delete(&event);

    // Read third event
    if (!yaml_parser_parse(&parser, &event))
        return 0;

    // Check for the payload parameter
    if (strcmp((char *)event.data.scalar.value, "payload") != 0)
        return 0;
    yaml_event_delete(&event);

    // Read fourth event
    if (!yaml_parser_parse(&parser, &event))
        return 0;

    // Check for the Create type
    if (strcmp((char *)event.data.scalar.value, "Create") != 0)
        return 0;
    yaml_event_delete(&event);

    // Return success
    return 1;
}