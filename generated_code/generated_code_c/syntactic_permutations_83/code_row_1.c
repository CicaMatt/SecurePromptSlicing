#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "request.h"
#include "response.h"

int main(void)
{
    char *name;
    while (1)
    {
        request_t r = receive_request();
        name = get_field(&r, "name");
        if (name != NULL && strlen(name) > 0)
        {
            response_t resp = create_response();
            set_body(&resp, name);
            send_response(&resp);
        }
    }
}