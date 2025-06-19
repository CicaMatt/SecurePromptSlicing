public static void copy(int dest, int src, int n) { 
        for (int i = 0; i < n; i++) { 
            System.arraycopy(src + i, dest + i, 1); 
         } 
     }