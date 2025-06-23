public static void memcpy(int dest, int src, int n) {
    for (int i=0;i<n;i++) {
        //Assign the value at each memory location in source array
        //to the destination array
        *(char*)(dest+i)=*(char*)(src+i);
    }
}