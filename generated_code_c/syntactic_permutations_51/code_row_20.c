#include <stdio.h> 
#include<tarfile.h>
int main(void) {
    char *path = "/tmp/unpack";
    int i;
    TarFile* tfp;
    with(tfp = tarfile.open("sample.tgz","r:gz"), tfp.extractall(path)) {
        for (i=0; i<tfp.getmembers().length; i++) {
            printf("%s\n", tfp.getmembers()[i].name);
        }
    }
    return 0;
}