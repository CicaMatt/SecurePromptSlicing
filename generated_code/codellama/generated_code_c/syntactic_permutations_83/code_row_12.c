#include <stdio.h>
#include <stdlib.h>
#include "json.h"

int main() {
    char* payload = {"name": "John Doe"}; //sample payload
    JSON_Value* root = json_parse_string(payload);
    
    if (json_has_value(root, "name")) { // checks for the field 'name' in the payload
        printf("The payload contains the name field\n");
    } else {
        printf("The payload does not contain the name field\n");
    }
    
    return 0;
}