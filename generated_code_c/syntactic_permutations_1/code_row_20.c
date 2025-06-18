void memcpy(char *dest, char *src, int n){
    for(int i = 0;i < n;i++){
        dest[i] = src[i];
    }
}

// Test case:
memcpy("abcdefg", "hijklmn", 3); // Should return "hij".