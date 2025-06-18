#include <stdio.h>
#include <string.h> 
int main() {
    FILE *fp;
    fp = fopen("file1.txt", "r");
    char buffer[256];
    if (fp) {
        while (!feof(fp)) {
            fgets(buffer, 256, fp);
        }
    }
    fclose(fp);

    int sum = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        sum += buffer[i];
    }
    if (sum == 0) {
        FILE *fp2;
        fp2 = fopen("file2.txt", "w");
        fprintf(fp2, "%s", buffer);
        fclose(fp2);
    }
}