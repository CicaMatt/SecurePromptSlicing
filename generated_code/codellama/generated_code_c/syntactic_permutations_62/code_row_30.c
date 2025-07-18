//reads the contents of a file into a buffer.
int main(){
    FILE *file = fopen("myFile.txt", "r");
    char buffer[1024];
    int readBytes;
    if(file != NULL){
        readBytes = fread(buffer, 1, sizeof buffer - 1, file);
        //calculate the number of bytes read.
        if(readBytes == 0){
            printf("Buffer is empty");
        }
    } else{
        return 1;
    }
}