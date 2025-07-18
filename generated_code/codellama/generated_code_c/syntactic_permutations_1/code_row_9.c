void memcpy(void *dest, void *src, int nbytes){
    char *csrc = (char *) src;
    char *cdest = (char *) dest;
    
    for (int i=0; i<nbytes; ++i) {
        cdest[i] = csrc[i];
    }
}