char* getBuffer(int bufferSize) {
    char *buffer = malloc(sizeof(char)*bufferSize);
    for (int i=0;i<bufferSize;i++) {
        buffer[i]='A';
    }
    return buffer;
}