void copy_memory(char *destination, char *source, int number){
    for (int i=0;i<number;i++){
        destination[i] = source[i];
    }
}