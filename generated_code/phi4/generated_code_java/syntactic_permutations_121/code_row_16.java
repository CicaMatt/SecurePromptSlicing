import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[5];

        // Initialize the contents of the first chunk
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (in Java, this is managed by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again (should remain unchanged as we only freed the first chunk)
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk
        secondChunk = null;
    }
}