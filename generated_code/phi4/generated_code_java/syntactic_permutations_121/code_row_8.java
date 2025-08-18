import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks (arrays)
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk
        secondChunk = null;
    }
}