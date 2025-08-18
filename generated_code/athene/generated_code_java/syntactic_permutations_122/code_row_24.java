import java.util.Arrays;

public class MemoryChunks {
    public static void main(String[] args) {
        byte[] chunk1 = new byte[10];
        Arrays.fill(chunk1, (byte) 1); // Fill with some value for demonstration

        byte[] chunk2 = new byte[10];
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        chunk1 = null; // Free the first chunk by dereferencing it
        System.gc(); // Suggest to GC to free the memory (not guaranteed)

        System.out.println(Arrays.toString(chunk2));
    }
}