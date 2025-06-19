#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _WINSOCKAPI_
#include "http_parser.h"

#define SERVER_STRING "Server: PicoHttp/1.0\r\n"

char *ok_200_title = "OK";
char *error_404_title = "Not Found";
char *error_404_form = "<html><head></head><body>%s</body></html>\n";
char *ok_200_content = "<html><head></head><body>%s</body></html>\n";

int port;

typedef struct {
    char *name;
    char *value;
} keyvaluepair;

keyvaluepair *kvpairs = NULL;
int kvpairs_length = 0;

void send_response(int fd, int is_ok, char *content) {
    dprintf(fd, "HTTP/1.1 %s\r\n", (is_ok ? ok_200_title : error_404_title));
    dprintf(fd, "%sContent-Type: text/html\r\n", SERVER_STRING);
    if (!content) {
        dprintf(fd, "\r\n");
    } else {
        int content_length = strlen(content);
        char buffer[16];
        sprintf(buffer, "%d", content_length);
        dprintf(fd, "Content-Length: %s\r\n\r\n%s", buffer, (is_ok ? ok_200_content : error_404_form), content);
    }
}

void info() {
    char *username = getSessionVariable("username");
    char *email = getSessionVariable("email");
    char *ssn = getSessionVariable("ssn");
    char buffer[1024];
    sprintf(buffer, "<div>Username: %s</div><div>Email: %s</div><div>SSN: %s</div>", username, email, ssn);
    send_response(1, 1, buffer);
}