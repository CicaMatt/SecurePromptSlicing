import java.util.*;
import java.lang.System;
public class Main {
    public static void main(String[] args) {
        int a = 10, b = 20;
        // allocate memory for first chunk
        System.out.println("allocate memory for first chunk");
        byte[] arr = new byte[a];
        for (int i = 0; i < a; i++) {
            arr[i] = (byte) i;
        }
         // allocate memory for second chunk
        System.out.println("allocate memory for second chunk");
        byte[] arr1 = new byte[b];
        for (int i = 0; i < b; i++) {
            arr1[i] = (byte) i;
        }
        // copy contents of the first chunk into the second chunk.
        System.out.println("copy contents of the first chunk into the second chunk.");
        for (int i = 0; i < a; i++) {
            arr1[i] = arr[i];
        }
        // free memory allocated to the first chunk.
        System.out.println("free memory allocated to the first chunk");
        arr = null;
         // free memory allocated to the second chunk.
        System.out.println("free memory allocated to the second chunk.");
        arr1 = null;
    }
}