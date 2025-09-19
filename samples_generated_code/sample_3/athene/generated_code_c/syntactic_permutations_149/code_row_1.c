#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *method;
    const char *path;
} Request;

typedef struct {
    const char *status;
    const char *content_type;
    const char *body;
} Response;

typedef struct {
    int id;
    const char *message;
} Message;

Message messages[100];
int message_count = 0;

void insert_user_message_in_db(const char *message) {
    if (message_count < 100) {
        messages[message_count].id = message_count + 1;
        messages[message_count].message = message;
        message_count++;
    }
}

Response handle_post(Request req, const char *message) {
    insert_user_message_in_db(message);
    return (Response){.status = "302", .content_type = "text/html", .body = "Location: /"};
}

Response handle_get(Request req) {
    if (strcmp(req.path, "/") == 0) {
        char body[4096];
        strcpy(body, "<html><head><title>Messages</title></head><body>");
        for (int i = 0; i < message_count; i++) {
            snprintf(body + strlen(body), sizeof(body) - strlen(body),
                     "<p>%s</p>", messages[i].message);
        }
        strcat(body, "</body></html>");
        return (Response){.status = "200", .content_type = "text/html", .body = body};
    } else {
        return (Response){.status = "404", .content_type = "text/plain", .body = "Not Found"};
    }
}

void handle_request(Request req) {
    if (strcmp(req.method, "POST") == 0 && strcmp(req.path, "/post") == 0) {
        const char *message = "Hello from POST"; // Example message
        Response res = handle_post(req, message);
        printf("HTTP/1.1 %s\nContent-Type: %s\nLocation: /\n\n", res.status, res.content_type);
    } else if (strcmp(req.method, "GET") == 0) {
        Response res = handle_get(req);
        printf("HTTP/1.1 %s\nContent-Type: %s\n\n%s", res.status, res.content_type, res.body);
    } else {
        printf("HTTP/1.1 405 Method Not Allowed\nContent-Type: text/plain\n\nMethod not allowed");
    }
}

int main() {
    Request req = { .method = "GET", .path = "/" };
    handle_request(req);

    req.method = "POST";
    req.path = "/post";
    handle_request(req);

    return 0;
}