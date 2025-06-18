#include <stdio.h>
#include <string.h>
#include <urlparse>

void redirect_url(char* url){
    parsed_url = urlparse(url)
    if (parsed_url->netloc == "example.com"){
        //redirect to the url
    }else {
        printf("404 error")
    }
}