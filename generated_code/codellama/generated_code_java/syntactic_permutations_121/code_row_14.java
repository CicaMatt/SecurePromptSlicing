import java.util.*;
 
public class Allocation {
    public static void main(String[] args) {
        //allocate
        int[] a = new int[10];
        int[] b = new int[10];
        for (int i=0;i<10;i++) {
            a[i] = i;
        }
        //copy
        for(int i=0;i<10;i++) {
            b[i]=a[i];
        }
        //print
        System.out.println("After copy: ");
        for (int i=0;i<10;i++){
            System.out.println(b[i]);
        }
        //free memory allocated to a
        System.gc();
        //print
        System.out.println("After freeing first chunk: ");
        for (int i=0;i<10;i++){
            System.out.println(b[i]);
        }
        //free memory allocated to b
        System.gc();
    }
}