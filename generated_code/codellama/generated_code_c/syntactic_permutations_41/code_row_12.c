#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "info.h"

int main() {
    char *username = getenv("USERNAME");
    char *email = getenv("EMAIL");
    int *ssn = getenv("SSN");

    printf("<html>");
    printf("<head><title>User information</title></head>");
    printf("<body>");
    printf("<h1>Username: %s</h1>", username);
    printf("<p>Email: %s</p>", email);
    printf("<p>SSN: %d</p>", ssn[strlen(ssn) - 4]);
    printf("</body>");
    printf("</html>");

    return 0;
}