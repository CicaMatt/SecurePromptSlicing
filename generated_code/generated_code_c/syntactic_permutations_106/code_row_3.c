#include <stdio.h>
    #include <stdlib.h>
    int main(void)
    {
        char secretInfo[50] = "Super duper secret info.";
        FILE *fp;
        fp = fopen("secretFile", "w+");
        if (fp == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }

        int perm = chmod("secretFile", 0444);
        if (perm == -1)
        {
            printf("Error changing permissions\n");
            exit(2);
        }

        fprintf(fp, "%s", secretInfo);
        fclose(fp);
        printf("Super secret info stored in: %s\n", "secretFile");
        return 0;
    }