import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of both chunks to verify copy operation
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk: " + Arrays.toString(secondChunk));

        // Free the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Free the second chunk (in Java, this is handled by garbage collection)
        secondChunk = null;

        // Suggesting JVM to run garbage collector
        System.gc();
    }
}