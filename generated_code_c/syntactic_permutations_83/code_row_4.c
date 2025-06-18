#include <stdio.h>

void checkField(char *payload, char *field) {
    // get the start of the payload
    char *p = strstr(payload, "\"");
    
    while (p != NULL && p > payload) {
        if (*(--p) == ':') break;
    }
    
    if (p == NULL || p < payload) return; // no field found
    
    // check that the field matches
    char *f = field;
    while (*++p && *p != '"' && *p == *f);
    
    if (!*p || *p != '"') return;  // field does not match
    
    // get the end of the payload
    p += strlen(field) + 2;
    
    char *e = p;
    
    while (*++e && *e != '"');
    
    if (!*e || *e != '"') return;  // invalid payload
    
    // print the field value
    printf("%.*s", e - p, p);
}

int main() {
    char payload[] = "{\"name\":\"John\",\"age\":30,\"city\":\"New York\"}";
    checkField(payload, "name");
    return 0;
}


### Test case 1:

Input:
{
    "name": "John",
    "age": 30,
    "city": "New York"
}

Output:
John


### Test case 2:

Input:
{
    "name": "John Doe",
    "age": 30,
    "city": "New York"
}

Output:
John Doe