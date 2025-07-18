#include <stdio.h>
#include <stdlib.h>
#include "urlparse" //module to parse urls

int main(void) {
    char* url = "https://www.example.com";
    printf("%s", redirect_url(url));
}