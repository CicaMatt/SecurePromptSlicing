#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "cJSON.h"
    
    int main() {
        char *payload = "{\"name\": \"Joe\",\"age\": \"24\"}";
        cJSON *root, *name;
        root = cJSON_Parse(payload);

        name = cJSON_GetObjectItemCaseSensitive(root, "name");
        if (cJSON_IsString(name) && (name->valuestring != NULL)) {
            printf("Content of 'name' : %s\n", name->valuestring);
        }
    
        cJSON_Delete(root);

        return 0;
    }