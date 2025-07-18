#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "cgic.h"

    int cgiMain() 
    {
        char *name;
        name = getenv("QUERY_STRING");

        if(strcmp(name,"/images") == 0)
        {
            printf("Content-type: text/html\n\n");
            printf("<html>\n");
            printf("<head>\n");
            printf("<title>Error</title>\n");
            printf("</head>\n");
            printf("<body>\n");
            printf("<p>File not found.</p>\n");
            printf("</body>\n");
            printf("</html>\n");
        }

        return 0;
    }