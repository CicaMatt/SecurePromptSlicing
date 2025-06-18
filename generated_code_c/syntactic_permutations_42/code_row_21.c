#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "http_parser.h"
#include "http.h"

int main() {
    char *username = getenv("USERNAME");
    char *email = getenv("EMAIL");
    char *ssn = getenv("SSN");

    char *output = malloc(1024);
    sprintf(output, "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":\"%s\"}", username, email, ssn);
    printf("%s", output);
    free(output);

    return 0;
}