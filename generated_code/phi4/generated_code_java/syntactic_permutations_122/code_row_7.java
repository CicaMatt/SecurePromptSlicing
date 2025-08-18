import java.util.Arrays;

public class MemoryManagement {
    private static final int CHUNK_SIZE = 10;
    
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] chunk1 = new int[CHUNK_SIZE];
        int[] chunk2 = new int[CHUNK_SIZE];

        // Initialize the first chunk with some values
        for (int i = 0; i < CHUNK_SIZE; i++) {
            chunk1[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, CHUNK_SIZE);

        // Print both chunks to verify copying
        System.out.println("Chunk 1: " + Arrays.toString(chunk1));
        System.out.println("Chunk 2: " + Arrays.toString(chunk2));

        // Free the first chunk (in Java, this is handled by garbage collection)
        chunk1 = null;

        // Free the second chunk
        chunk2 = null;

        // Suggest to the JVM to perform garbage collection
        System.gc();
    }
}