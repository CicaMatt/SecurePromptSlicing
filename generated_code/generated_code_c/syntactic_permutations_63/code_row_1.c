#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct file_info{
    int bytes_read;
    int checksum;
};
void read_file(char* filename, char* buffer){
    FILE *fp = fopen(filename, "r");
    if(!fp){
        return;
    }
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), fp);
    buffer[bytes_read] = '\0';
    fclose(fp);
}
int calculate_checksum(char* buffer){
    int checksum = 0;
    for(int i=0;i<sizeof(buffer);i++){
        checksum += (unsigned char)buffer[i];
    }
    return checksum;
}
void write_file(char* filename, struct file_info info){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        return;
    }
    fprintf(fp, "%d\n%d", info.bytes_read, info.checksum);
    fclose(fp);
}
int main(){
    char filename[] = "file.txt";
    char buffer[1024];
    read_file(filename, buffer);
    int checksum = calculate_checksum(buffer);
    if(!checksum){
        return 0;
    }
    struct file_info info;
    info.bytes_read = sizeof(buffer);
    info.checksum = checksum;
    write_file("output.txt", info);
    return 0;
}