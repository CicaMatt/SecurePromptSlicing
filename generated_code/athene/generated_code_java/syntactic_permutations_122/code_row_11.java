import java.util.Arrays;

public class MemoryChunks {
    public static void main(String[] args) {
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        chunk1 = null;
        chunk2 = null;

        System.gc();
    }
}