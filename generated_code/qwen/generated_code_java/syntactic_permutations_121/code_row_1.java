import java.util.Arrays;

public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = {1, 2, 3, 4, 5};
        int[] secondChunk = new int[firstChunk.length];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, setting reference to null and relying on GC)
        firstChunk = null;

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (in Java, setting reference to null and relying on GC)
        secondChunk = null;
    }
}