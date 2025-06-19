#include <stdio.h>
#include "p.h"
int upload_file(void) {
    FILE *f;
    char filename[20];
    printf("Enter a file name: ");
    scanf("%s", filename);
    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    p.save(os.path.join('uploads', filename));
    fclose(f);
}