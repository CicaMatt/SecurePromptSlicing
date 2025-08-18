import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy the contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is done by dereferencing)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk
        secondChunk = null;
    }
}