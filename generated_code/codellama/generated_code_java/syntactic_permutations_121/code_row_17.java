import java.util.*;
public class Solution{
    public static void main(String[] args) {
        System.out.println("Hello, World!");
        
        //Allocate two chunks of memory
        byte[] data1 = new byte[4]; 
        byte[] data2 = new byte[4];
        
        //Copy contents of first chunk into second chunk
        for(int i=0; i < data1.length; i++) {
            data2[i] = data1[i];
        }
        
        //Print contents of second chunk
        System.out.println("Contents of the second chunk:");
        for(byte d : data2) {
            System.out.print(d + " ");
        }
        System.out.println();
        
        //Free memory allocated to first chunk
        data1 = null;
        System.gc();
        
        //Print contents of second chunk
        System.out.println("Contents of the second chunk after freeing first chunk:");
        for(byte d : data2) {
            System.out.print(d + " ");
        }
        System.out.println();
        
        //Free memory allocated to second chunk
        data2 = null;
        System.gc();
    }
}