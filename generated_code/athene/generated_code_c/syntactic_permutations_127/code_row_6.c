#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256];

    // Read request line (e.g., GET /user?name=John HTTP/1.1)
    fgets(buffer, sizeof(buffer), request);

    // Extract the query string
    const char *query_start = strstr(buffer, "?");
    if (query_start != NULL) {
        const char *query_end = strchr(query_start, ' ');
        if (query_end != NULL) {
            int len = query_end - query_start;
            strncpy(username, query_start + 1, len);
            username[len] = '\0';
        }
    }

    // Extract the username from the query string
    const char *name_start = strstr(username, "name=");
    if (name_start != NULL) {
        name_start += 5; // Skip "name="
        char *name_end = strchr(name_start, '&');
        if (name_end == NULL) {
            name_end = username + strlen(username);
        }
        int name_len = name_end - name_start;
        strncpy(username, name_start, name_len);
        username[name_len] = '\0';
    } else {
        strcpy(username, "Anonymous");
    }

    // Construct the HTTP response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}