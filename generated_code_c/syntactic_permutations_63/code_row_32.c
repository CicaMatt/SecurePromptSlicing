// To store the contents of the file in buffer
int size = 1024;
char buffer[size];
FILE *file = fopen("file_name", "r");
fread(buffer, sizeof(char), size, file);
// Calculate checksum
unsigned int checksum = 0;
for (int i=0;i<size;i++){
   checksum += buffer[i];
}
if (checksum == 0){
    printf("Buffer is empty.\n");
}
fclose(file);