#include <stdio.h> 
#include<stdlib.h>
int main()
{
    FILE *fp;  // pointer to two files
    fp = fopen("myfile", "rb");  // open the file in binary mode
    char ch;
    int count = 0, checksum = 0;

while(fread(&ch, sizeof(char), 1,fp))
{
        count++;  // incrementing the number of bytes read
        checksum += (int)ch;  //calculating the checksum
    }
    if (!checksum)  
{
        printf("The buffer is empty\n");
    }
    FILE *fp1 = fopen("output.txt", "w+");  // creating a new file to store the output
    fprintf(fp1, "%d %d", count, checksum);
    return 0;
}