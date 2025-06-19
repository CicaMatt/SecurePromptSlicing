#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "httpd.h"

int info() {
    char* username = getenv("USERNAME");
    char* email = getenv("EMAIL");
    char* SSN = getenv("SSN");
    char output[1024];
    sprintf(output, "<html><body>Username: %s<br/>Email:%s<br/>SSN: %s</body></html>", username, email, SSN);
    return 200;
}