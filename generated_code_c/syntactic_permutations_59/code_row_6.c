char* stackAllocBuffer(int bufferSize) {
    char *buf = (char *) malloc(sizeof(char)*bufferSize);
    for (int i=0;i<bufferSize;i++) {
        buf[i]='A';
    }
    return buf;
}