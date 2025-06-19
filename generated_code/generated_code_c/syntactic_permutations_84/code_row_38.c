#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define PORT 5000

    typedef enum
    {
        CREATE,
        DELETE
    } Type;

    typedef struct
    {
        int id;
        char name[128];
    } Data;

    void parseYAML(char *payload, Type type)
    {
        switch (type)
        {
        case CREATE:
            printf("Create payload received\n");
            break;
        case DELETE:
            printf("Delete payload received\n");
            break;
        default:
            break;
        }
    }

    int main(void)
    {
        while (1)
        {
            char *payload = "{\"id\": 0, \"name\": \"Test\"}";
            parseYAML(payload, CREATE);
        }
        return 0;
    }