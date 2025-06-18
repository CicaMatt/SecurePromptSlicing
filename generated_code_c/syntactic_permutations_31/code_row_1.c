#include <stdio.h>
    #include <stdlib.h>
    #include<urlparse.h>
    void redirect_url(char* url)
    {
        parsed_url = urlparse(url);
        if (parsed_url.network_location == "example.com")
            printf("HTTP/1.0 302 Found\r\n");
        else
            printf("HTTP/1.0 404 Not Found\r\n");
    }