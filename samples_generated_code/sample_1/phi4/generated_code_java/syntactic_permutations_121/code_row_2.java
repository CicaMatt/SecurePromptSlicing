import java.util.Arrays;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the contents of the first chunk
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java this is automatic garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Explicitly suggest to free the second chunk as well
        secondChunk = null;
    }
}