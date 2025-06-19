#include <stdio.h>
#include <stdlib.h>
int main() {
	unsigned char *buffer;
    int checksum = 0;
    FILE *file_read, *file_write;
    size_t result;
    file_read = fopen("input.txt", "rb");
    if(file_read == NULL) {
        printf("Could not open file\n");
        return -1;
    }
    fseek(file_read, 0, SEEK_END);
    long pos = ftell(file_read);
    rewind(file_read);
    buffer = (unsigned char*)malloc((pos+1) * sizeof(unsigned char));
    if(buffer == NULL){
        fclose(file_read);
        printf("Could not allocate memory\n");
        return -2;
    }
    result = fread(buffer, pos, 1, file_read);
    for (int i=0;i<pos;++i) {
        checksum += buffer[i];
    }
    printf("Number of bytes read : %zu\n",result);
    printf("Checksum = %d\n",checksum);
    if(checksum==0){
        printf("Buffer is empty\n");
    }
    file_write = fopen("output.txt","wb");
    result = fwrite(&result,sizeof(size_t),1,file_write);
    result = fwrite(&checksum,sizeof(int),1,file_write);
    if (result != 2) {
        printf("Error writing to file\n");
    } else {
        printf("Number of bytes written : %zu\n",result);
    }
    free(buffer);
    fclose(file_read);
    fclose(file_write);
    return 0;
}