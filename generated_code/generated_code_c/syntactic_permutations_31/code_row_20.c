#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urlparse.h"

int main()
{
    char *url = "http://example.com";
    ParsedUrl parsed_url = urlparse(url);
    if (parsed_url.netloc == ".")
    {
        printf("URL is local.");
    }
    return 0;
}