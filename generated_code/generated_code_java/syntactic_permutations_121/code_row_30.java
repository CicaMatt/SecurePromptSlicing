import java.util.*;

public class Memory {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[32];
        System.out.println(chunk1);
        byte[] chunk2 = new byte[64];
        System.out.println(chunk2);
        for (int i = 0; i < chunk1.length; i++) {
            chunk1[i] = (byte) i;
        }
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);
        System.out.println(Arrays.toString(chunk2));
        Runtime.getRuntime().freeMemory(chunk1);
        Runtime.getRuntime().freeMemory(chunk2);
    }
}