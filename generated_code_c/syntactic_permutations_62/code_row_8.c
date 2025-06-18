#include <stdio.h>
int main() {
    unsigned char buf[128];
    int n = 0;
    int cksum = 0;
    FILE *fp;
    fp = fopen("file.txt", "r");
    if (fp != NULL) {
        n = fread(buf, sizeof(unsigned char), 128, fp);
        for (int i = 0; i < n; i++)
            cksum += buf[i];
        printf("%d\n", cksum);
    } else {
        printf("Error opening file");
    }
    if (cksum == 0)
        printf("The buffer is empty\n");
    fclose(fp);
    return 0;
}