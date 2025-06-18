#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_last_four(int num) {
    char str[12];
    sprintf(str, "%06d", num);
    return &str[2];
}

void info(request req, response res) {
    const char *username = "john.doe";
    const char *email = "john.doe@example.com";
    int social_security_number = 123456789;
    char* last_four = get_last_four(social_security_number);
    char html[400];
    sprintf(html, "<!DOCTYPE html><html><body>Username: %s<br/>Email: %s<br/>Last 4 digits of SSN: %s</body></html>", username, email, last_four);
    res.setHeader("Content-Type", "text/html");
    res.send(200, html);
}