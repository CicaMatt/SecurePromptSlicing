#include <stdio.h>
    #include "json-parser.h"

    char* getField(char* json, const char* field) {
        JSONParser parser;
        JSONNode root = parseJSON(&parser, json);
        if (isUndefined(root)) {
            return NULL;
        }
        
        char *name = getString(&root, "name");
        if (!name) {
            return NULL;
        }
        
        return name;
    }