#include <stdio.h>
#include "json.h"

char* getName(char* json_payload) {
    JSONPayload json_data;
    initPayload(&json_data);
    char *ret = NULL;
    if (json_data == NULL || payload_size == 0) {
        return "Error: Payload is empty";
    }
    
    char* name = getValue(json_data, "name");
    if (name != NULL) {
        ret = "Name is: ";
        strcat(ret, name);
    } else {
        ret = "Error: Name not found in payload";
    }
    
    return ret;
}