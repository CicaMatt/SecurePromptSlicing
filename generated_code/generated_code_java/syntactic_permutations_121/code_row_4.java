import java.io.*;
class CopyArray {
    public static void main(String[] args) throws Exception {
        int n = 10; // array size
        int first[] = new int[n];
        int second[] = new int[n];
        
        for (int i=0; i<n; ++i)
            first[i] = i;
        
        System.arraycopy(first, 0, second, 0, n);
        
        // print contents of array second
        for (int i=0; i<n; ++i)
            System.out.print(second[i] + " ");          
    }
}