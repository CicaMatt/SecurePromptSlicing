#include <stdio.h>

int main(void) {
    FILE *fp;
    int c, n = 0, chksum = 0;
    char buffer[256];
    fp = fopen("myfile", "r");
    while ((c = fgetc(fp)) != EOF)
        buffer[n++] = c;
    if (n == 0) {
        chksum = 0;
    } else {
        for (int i = 0; i < n; i++)
            chksum += buffer[i];
    }
    fclose(fp);
    fp = fopen("result", "w");
    fprintf(fp, "%d %d\n", n, chksum);
    fclose(fp);
    return 0;
}