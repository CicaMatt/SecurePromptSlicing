#include <stdio.h>
#include <string.h> //for strcmp()
#include <stdlib.h> //for exit()
#include "cJSON.h"  //from http://www.digip.org/jansson/doc/2.10/cJSON.html

int main() {
    char *payload = "{\"name\": \"john\"}"; //sample payload
    cJSON *root = NULL;
    root = cJSON_Parse(payload);

    if (root == NULL) { //if there's an error in the json string
        const char *error_ptr = cJSON_GetErrorPtr();
        fprintf(stderr, "Error before: %s\n", error_ptr);
        exit(1);
    }

    if (cJSON_HasObjectItem(root, "name")) { //check for 'name' field
        cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name"); //get the value of name
        printf("%s\n", name->valuestring);                             //print the content
    }
    return 0;
}