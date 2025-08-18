import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate memory chunks (arrays)
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Output to show copying was successful
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk));

        // Freeing memory (in Java, this is handled by the garbage collector)
        // Explicitly set references to null
        firstChunk = null;
        secondChunk = null;

        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();

        // Optionally, you can check if objects are collected (for demonstration purposes)
        System.out.println("First Chunk after freeing: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk after freeing: " + Arrays.toString(secondChunk));
    }
}