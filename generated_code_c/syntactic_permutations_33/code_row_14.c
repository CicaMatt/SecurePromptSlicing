#include <stdio.h>
#include <stdlib.h>

void redirect_invalid_url(char* url);
int main(void) {
    char* url = "https://www.example.com";
    redirect_invalid_url(url);
    return 0;
}

void redirect_invalid_url(char* url){
    printf("URL: %s", url);
     if (strstr(url, ".com")) {
        printf("Valid URL");
    } else {
        printf("Invalid URL. Redirecting to default page.");
    }
}