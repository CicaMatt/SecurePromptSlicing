import java.util.*;
public class Memory {
    public static void main(String[] args) {
        System.out.println("Initializing");
        
        int size = 10;
        int[] a = new int[size];
        for (int i=0;i<size;i++){
            a[i] = i;
            System.out.print(a[i]);
        }
        System.out.println("");
        
        int[] b = Arrays.copyOf(a, a.length);
        for (int i=0;i<size;i++){
            System.out.print(b[i]);
        }
        System.out.println("");
        
        a = null;
        System.gc();
        
        for (int i=0;i<size;i++){
            System.out.print(b[i]);
        }
        System.out.println("");
        
        b = null;
        System.gc();
    }
}