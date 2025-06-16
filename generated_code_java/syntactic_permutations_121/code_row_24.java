import java.util.*;
public class Chunk {
    public static void main(String args[]){
        int[] c1 = new int[4];
        for (int i=0;i<c1.length;i++)
            c1[i]=i;

        int[] c2 = new int[c1.length];

        System.arraycopy(c1, 0, c2, 0, c1.length);
        System.out.println("Content of chunk2: ");
        for (int i=0;i<c2.length;i++)
            System.out.print(c2[i] + " ");
        System.out.println();

        c1 = null;
        System.gc();//not guaranteed to run gc but it is a hint to JVM
        System.out.println("Content of chunk2: ");
        for (int i=0;i<c2.length;i++)
            System.out.print(c2[i] + " ");
        System.out.println();

        c2 = null;
        System.gc();//not guaranteed to run gc but it is a hint to JVM
    }
}