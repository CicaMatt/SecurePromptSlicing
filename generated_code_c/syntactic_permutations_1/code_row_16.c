void copy_bytes(char *dest, char *src, int n){
    for(int i=0;i<n;++i) dest[i] = src[i];
}

// Example Usage:
char src[]="I am here";
char dest[sizeof(src)];
copy_bytes(dest,src,sizeof(src));
printf("%s",dest);