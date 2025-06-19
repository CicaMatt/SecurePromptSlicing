#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "cJSON.h"
    
    char* get_name(char* payload) {
        cJSON *root = cJSON_Parse(payload);
        if (root == NULL) {
            const char *error_ptr = cJSON_GetErrorPtr();
            return error_ptr;
        }
        cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
        if (!cJSON_IsString(name)) {
            cJSON_Delete(root);
            return NULL;
        }
        char* result = name->valuestring;
        cJSON_Delete(root);
        return result;
    }