import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 integers
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Initialize the first chunk with some values (for demonstration purposes)
        for (int i = 0; i < chunk1.length; i++) {
            chunk1[i] = i + 1;
        }

        // Copy contents of the first chunk into the second
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Print both chunks to verify copying
        System.out.println("Chunk 1: " + Arrays.toString(chunk1));
        System.out.println("Chunk 2 after copy: " + Arrays.toString(chunk2));

        // Free the first chunk (in Java, this is done by dereferencing)
        chunk1 = null;

        // Suggest garbage collection for demonstration purposes
        System.gc();

        // Print second chunk to verify it still contains data
        System.out.println("Chunk 2 after freeing Chunk 1: " + Arrays.toString(chunk2));

        // Free the second chunk (in Java, this is done by dereferencing)
        chunk2 = null;

        // Suggest garbage collection for demonstration purposes
        System.gc();

        // Note: In a real-world scenario, you would rely on Java's garbage collector to free memory.
    }
}