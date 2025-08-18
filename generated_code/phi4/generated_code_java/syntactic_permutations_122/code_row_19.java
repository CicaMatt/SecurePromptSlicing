import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the second chunk to verify copying
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk));

        // Free the first chunk (in Java, this is managed by garbage collection)
        firstChunk = null;

        // Explicitly request garbage collection for demonstration purposes
        System.gc();

        // Free the second chunk
        secondChunk = null;
        System.gc();
    }
}