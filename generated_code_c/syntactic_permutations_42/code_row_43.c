#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
int main() {
    char *username = "user";
    char *email = "email@domain.com";
    int ssn = 123456789;
    info(username, email, ssn);
}


### Response:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
char *info(char *username, char *email, int ssn) {
    int size = 1024;
    char *data = malloc(size);
    int len = snprintf(data, size - 1, "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":%d}", username, email, ssn);
    data[len] = '\0';
    return data;
}


### Response:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *info(char *username, char *email, int ssn) {
    int size = 1024;
    char *data = malloc(size);
    int len = snprintf(data, size - 1, "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":%d}", username, email, ssn);
    data[len] = '\0';
    return data;
}


### Response:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *info(char *username, char *email, int ssn) {
    int size = 1024;
    char *data = malloc(size);
    int len = snprintf(data, size - 1, "{\"username\":\"%s\", \"email\":\"%s\", \"ssn\":%d}", username, email, ssn);
    data[len] = '\0';
    return data;
}