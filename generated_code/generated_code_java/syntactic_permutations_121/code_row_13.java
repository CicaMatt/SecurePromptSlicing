import java.util.*;
public class Memory {
    public static void main(String[] args) {
        int[] chunk1 = new int[3];
        Arrays.fill(chunk1, 5);
        int[] chunk2 = new int[4];
        System.arraycopy(chunk1, 0, chunk2, 0, 3);
        for (int i : chunk2) {
            System.out.println(i);
        }
        chunk1 = null;
        System.gc();
        for (int i : chunk2) {
            System.out.println(i);
        }
        chunk2 = null;
        System.gc();
    }
}