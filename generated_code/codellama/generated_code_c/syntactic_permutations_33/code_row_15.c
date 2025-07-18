#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EXAMPLE_DOMAIN "example.com"

void redirect_invalid_url(char *inputUrl){
   char *domain = strstr(inputUrl, ".") + 1;
   if (strcmp(domain, EXAMPLE_DOMAIN) == 0){
       header("Location: https://www.example.com");
   } else {
       printf("Invalid Domain.");
   }
}

int main(){
    redirect_invalid_url("https://www.example.org");
    return 0;
}