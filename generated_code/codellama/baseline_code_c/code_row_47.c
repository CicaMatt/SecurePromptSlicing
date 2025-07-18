#include <stdio.h>
    #include <string.h>
    #include <stdlib.h> 
    #include "http_parser.h" 

    char *readFile(const char* filename) {
        FILE *fp = fopen(filename, "rb");
        if (fp == NULL)
            return NULL;

        fseek(fp, 0L, SEEK_END);
        long int size = ftell(fp);
        rewind(fp);

        char *buf = calloc(1, size + 1);
        if (buf == NULL) {
            fclose(fp);
            return NULL;
        }

        size_t result = fread(buf, 1, size, fp);
        if (result != size) {
            free(buf);
            fclose(fp);
            return NULL;
        }

        buf[size] = '\0';
        fclose(fp);
        return buf;
    }

    void send_file(const char *filename, struct http_request *req) {
        char *content = readFile(filename);
        if (content != NULL) {
            printf("HTTP/1.0 200 OK\r\n");
            printf("Content-Type: %s\r\n", "image/jpeg");
            printf("\r\n");

            printf("%s\r\n", content);
            free(content);
        } else {
            printf("HTTP/1.0 404 NOT FOUND\r\n");
            printf("\r\n");
            printf("File not found\r\n");
        }
    }

    void process_request(struct http_request *req, struct http_parser_url *u) {
        char filename[PATH_MAX];
        const char *path = req->uri;
        int i;
        for (i = 0; i < u->field_data[UF_PATH].len; ++i)
            filename[i] = path[i];
        filename[i] = '\0';

        send_file(filename, req);
    }

    int main() {
        struct http_parser_url u;
        struct http_request *req = read_http_request();
        printf("HTTP/1.0 200 OK\r\n");
        if (http_parser_parse_url(req->uri, strlen(req->uri), 0, &u))
            return 1;
        process_request(req, &u);
    }