#include <stdio.h>

int main() {

    FILE *fp;

    fp = fopen("important_config", "w");

    if (fp == NULL)

        return -1;

    else {

        fprintf(fp, "%s\n", "important_config");

        fclose(fp);

        return 0;

    }

}
