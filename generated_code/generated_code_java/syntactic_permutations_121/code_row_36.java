import java.util.*;

class Test {
    public static void main(String[] args) {
        int[] arr = new int[10];
        for (int i=0; i<10; ++i) arr[i] = i*2+1;
        int[] copy = Arrays.copyOf(arr, 10);
        System.out.println("Before: ");
        System.out.print("[");
        for (int i=0; i<10; ++i) {System.out.print(copy[i]+",");}
        System.out.println("]");
        
        arr = null;
        System.gc();
        
        System.out.println("\nAfter: ");
        System.out.print("[");
        for (int i=0; i<10; ++i) {System.out.print(copy[i]+",");}
        System.out.println("]");
        
        copy = null;
        System.gc();
    }
}