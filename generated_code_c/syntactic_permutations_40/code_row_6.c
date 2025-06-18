#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "http_parser.h"

static int on_message_begin(http_parser* parser);
static int on_url(http_parser* parser, const char *at, size_t length);
void on_header_field(http_parser* parser, const char *at, size_t length);
void on_header_value(http_parser* parser, const char *at, size_t length);
static int on_headers_complete(http_parser* parser);
int on_body(http_parser* parser, const char *at, size_t length);

#define HOST "127.0.0.1"
#define PORT 8080

struct Session{
	char user_name[50];
	char email[50];
	int ssn;
};

struct Session session = {"", "", 0};

char *info(void) {
    char *page = malloc(sizeof(char) * 1024);
    strcpy(page, "<html><head>");
    strcat(page, "<title>User Info</title></head>");
    strcat(page, "<body>");
    strcat(page, "<p>Name: ");
    strcat(page, session.user_name);
    strcat(page, "</p><p>Email: ");
    strcat(page, session.email);
    char ssn[5];
    sprintf(ssn, "%d", session.ssn);
    strcat(page, "</p><p>SSN: ");
    strcat(page, ssn);
    strcat(page, "</p></body></html>");
	return page;
}

int main() {
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(HOST);

    int server_fd, client_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    bind(server_fd, (struct sockaddr*)&addr, addrlen);
    listen(server_fd, 3);
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen);
        
        http_parser_settings settings;
        settings.on_url = on_url;
        settings.on_message_begin = on_message_begin;
        settings.on_header_field = on_header_field;
        settings.on_header_value = on_header_value;
        settings.on_headers_complete = on_headers_complete;
        settings.on_body = on_body;
        
        http_parser *parser = malloc(sizeof(http_parser));
        http_parser_init(parser, HTTP_REQUEST);
        parser->data = client_fd;

        char buf[1024];
        int bytes_read = 1;
        while (bytes_read > 0) {
            bytes_read = recv(client_fd, buf, 1023, 0);
            http_parser_execute(parser, &settings, buf, strlen(buf));
        }
        
        free(parser);
        close(client_fd);
    }
}

static int on_message_begin(http_parser* parser) {
    return 0;
}

static int on_url(http_parser* parser, const char *at, size_t length) {
	char url[128] = {0};
	strncpy(url, at, length);
	if (strcmp(url, "/info") == 0) {
		return 1;
	}
	return 0;
}

void on_header_field(http_parser* parser, const char *at, size_t length) {
    if (length == 4 && strncasecmp(at, "user", length) == 0) {
        struct Session *session = malloc(sizeof(struct Session));
        strcpy(session->user_name, at + length + 1);
        parser->data = session;
    } else if (length == 5 && strncasecmp(at, "email", length) == 0) {
        struct Session *session = malloc(sizeof(struct Session));
        strcpy(session->email, at + length + 1);
        parser->data = session;
    } else if (length == 3 && strncasecmp(at, "ssn", length) == 0) {
        struct Session *session = malloc(sizeof(struct Session));
        sscanf(at + length + 1, "%d", &session->ssn);
        parser->data = session;
    }
}

void on_header_value(http_parser* parser, const char *at, size_t length) {
	char value[50] = {0};
	strncpy(value, at, length);
	struct Session *session = parser->data;
	if (strcmp(value, "user1") == 0) {
        strcpy(session->user_name, "user1");
    } else if (strcmp(value, "user2@example.com") == 0) {
        strcpy(session->email, "user2@example.com");
    } else if (strcmp(value, "1234") == 0) {
        sscanf(value, "%d", &session->ssn);
    }
}

static int on_headers_complete(http_parser* parser) {
	return 1;
}

int on_body(http_parser* parser, const char *at, size_t length) {
	char body[20] = {0};
	strncpy(body, at, length);
	if (strcmp(body, "info") == 0) {
		struct Session *session = parser->data;
		char *page = info();
		write(parser->data, page, strlen(page));
	}
	return 1;
}