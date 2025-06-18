#include <stdio.h>
#include <stdlib.h> // for system()

void execute(const char* cmd)
{
    system(cmd);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        return 1;
    }

    char buf[512];
    sprintf(buf, "cat /etc/passwd | grep %s", argv[1]);

    execute(buf);
}