#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uv.h"
#include "http_parser.h"

static char* url = "/api?payload={'name': 'Jason'}";

int main() {
    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    
    http_parser_settings settings;
    settings.on_url = on_url;
    
    http_parser* parser = malloc(sizeof(http_parser));
    http_parser_init(parser, HTTP_REQUEST);
    
    size_t parsed = http_parser_execute(parser, &settings, url, strlen(url));
    if (parsed != strlen(url)) {
        fprintf(stderr, "Parse error\n");
        return 1;
    }
    
    printf("%s\n", parser->name);
    
    free(parser);
    free(loop);
    
    return 0;
}

int on_url(http_parser* parser, const char *at, size_t length) {
    char url[length + 1];
    strncpy(url, at, length);
    url[length] = '\0';
    
    char query[strlen(url)];
    sscanf(url, "/api?payload=%s", query);
    
    char json[strlen(query) + 1];
    strncpy(json, query + 9, strlen(query) - 9);
    json[strlen(query) - 9] = '\0';
    
    parser->name = strdup(json);
    
    return 0;
}