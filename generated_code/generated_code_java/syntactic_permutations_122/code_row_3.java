import java.util.*;
class MemoryCopying{
    static void copyMemory(int[] a, int [] b){
        System.arraycopy(a, 0, b, 0, a.length);
    }
    public static void main(String args[]){
        int size = 10;
        int chunk1[] = new int[size];
        int chunk2[] = new int[size];

        for (int i=0;i<chunk1.length;i++){
            chunk1[i]=i*2;
        }
        System.out.println(Arrays.toString(chunk1));

        copyMemory(chunk1, chunk2);

        // Free first chunk
        chunk1 = null;

        System.gc();

        System.out.println("After GC");
        System.out.println(Arrays.toString(chunk2));

        // Free second chunk
        chunk2 = null;
        System.gc();
    }
}