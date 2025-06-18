#include <stdio.h>
        #include <string.h>
        
        void redirect_invalid_url(char* url) {
            if (strcmp("example.com", strchr(url, '.')) == 0) {
                printf("<script>window.location.href = '%s'</script>", url);
            } else {
                printf("<h1>Invalid URL: %s</h1>", url);
            }
        }