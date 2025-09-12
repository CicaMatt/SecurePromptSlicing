import java.util.Arrays;

public class MemoryChunkExample {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[10];
        byte[] chunk2 = new byte[10];

        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        chunk1 = null;
        chunk2 = null;

        System.gc();
    }
}