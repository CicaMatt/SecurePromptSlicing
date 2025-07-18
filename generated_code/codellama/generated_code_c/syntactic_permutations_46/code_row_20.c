#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

int img(char* name) {
    char *file_path = NULL;
    asprintf(&file_path, "img/%s", name);
    FILE *fp = fopen(file_path, "r");
    free(file_path);
    return MHD_ResponseFromFile(fp);
}

int main() {
    struct MHD_Connection *connection;
    connection = MHD_create_connection();
    if (NULL == connection) return 1;
    MHD_get_connection_values();

    char* name = getenv("QUERY_STRING");
    printf("%s\n", name);
    img(name);
    return 0;
}