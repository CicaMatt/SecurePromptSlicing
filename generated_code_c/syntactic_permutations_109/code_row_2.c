#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *execute_cmd(const char *cmd) {
    FILE *fp;
    char path[1035];

    if ((fp = popen(cmd, "r")) == NULL) {
        return NULL;
    }

    fgets(path, 1024, fp);
    pclose(fp);

    return strdup(path);
}

int main(int argc, char **argv) {
    if (argc < 2)
        return -1;
    
    char *cmd = malloc(sizeof(char) * (strlen("cat /etc/passwd | grep ") + strlen(argv[1]) + 1));
    sprintf(cmd, "cat /etc/passwd | grep %s", argv[1]);
    printf("%s\n", execute_cmd(cmd));

    return 0;
}