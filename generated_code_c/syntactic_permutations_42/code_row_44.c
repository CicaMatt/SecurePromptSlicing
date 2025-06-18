#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"
int main(){
    char *username = getenv("USERNAME");
    char *email = getenv("EMAIL");
    int ssn = atoi(getenv("SSN"));
    return 0;
}