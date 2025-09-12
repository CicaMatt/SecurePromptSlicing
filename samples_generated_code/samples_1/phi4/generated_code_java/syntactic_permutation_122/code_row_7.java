import java.util.Arrays;

public class MemoryManagement {

    private static final int SIZE = 10;

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        byte[] firstChunk = new byte[SIZE];
        byte[] secondChunk = new byte[SIZE];

        // Initialize the first chunk with some data
        for (int i = 0; i < SIZE; i++) {
            firstChunk[i] = (byte) (i + 1);
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, SIZE);

        // Print both chunks to verify copying
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk before freeing first: " + Arrays.toString(secondChunk));

        // Free the first chunk (simulated by setting it to null)
        firstChunk = null;

        // Perform garbage collection (for demonstration purposes)
        System.gc();

        // Print second chunk after freeing the first
        System.out.println("Second Chunk after freeing first: " + Arrays.toString(secondChunk));

        // Free the second chunk (simulated by setting it to null)
        secondChunk = null;

        // Perform garbage collection again (for demonstration purposes)
        System.gc();
    }
}