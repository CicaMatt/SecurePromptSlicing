#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SESSION_USERNAME "user123"
#define SESSION_EMAIL "user@example.com"
#define SESSION_SSN "123-45-6789"

typedef struct {
    char *username;
    char *email;
    char *ssn;
} Session;

void print_info() {
    // Simulate session retrieval
    Session session = {SESSION_USERNAME, SESSION_EMAIL, SESSION_SSN};

    printf("Content-Type: text/html\r\n");
    printf("\r\n");
    printf("<html><body>");
    printf("<h1>User Information</h1>");
    printf("<p>Username: %s</p>", session.username);
    printf("<p>Email: %s</p>", session.email);
    printf("<p>Last 4 Digits of SSN: %c%c%c%c</p>",
           session.ssn[6], session.ssn[7], session.ssn[8], session.ssn[9]);
    printf("</body></html>");
}

int main(void) {
    const char *query_string = getenv("QUERY_STRING");
    
    if (strcmp(query_string, "info") == 0) {
        print_info();
    } else {
        printf("Content-Type: text/html\r\n");
        printf("\r\n");
        printf("<html><body>");
        printf("<h1>404 Not Found</h1>");
        printf("</body></html>");
    }

    return 0;
}


To run this code, you need to compile it and set up a CGI environment. For example:


gcc -o info.cgi your_code.c
chmod +x info.cgi

# Place `info.cgi` in the CGI directory of your web server, typically `/var/www/cgi-bin/`


Make sure your web server is configured to execute CGI scripts from that directory. Access it via a browser at: `http://yourserver.com/cgi-bin/info.cgi?info`.