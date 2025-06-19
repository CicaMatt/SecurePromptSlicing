#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    FILE *file_pointer; // declare a pointer to file
    char filename[256];  // Array to store the file name
    int bytes_read = 0; // variable to store the number of bytes read from the file
    unsigned short checksum = 0;// variable to store the check sum of the file
    char buffer[1024]; // character array to store the contents of the file
    printf("Enter name of file: ");
    fgets(filename, sizeof(filename), stdin);// read the file name from user using fgets
    filename[strcspn(filename, "\n")] = 0;// remove any trailing newlines
    if ((file_pointer = fopen(filename,"r")) == NULL) // try to open the file for reading.
    {                                     
        perror("Error opening file");  // print an error message and exit if that fails.
        exit(EXIT_FAILURE);             
    }                                    
    bytes_read = fread(buffer,1,sizeof(buffer),file_pointer);// Read the contents of the file into buffer
    while (bytes_read > 0)//while loop to read all the content of the file
    {  
        for(int i=0;i<bytes_read;i++)
        {                                               // Loop through each character in the buffer.
            checksum += buffer[i]; // Add it to the total.
        }
        bytes_read = fread(buffer,1,sizeof(buffer),file_pointer);// Read the next block of data into the buffer. 
    }
    printf("%d\n",checksum);//prints the check sum of file
    fclose(file_pointer); // close the file
    return 0;
}