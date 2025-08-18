import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate the first chunk of memory with some initial values
        int[] firstChunk = {1, 2, 3, 4, 5};

        // Allocate the second chunk of memory with the same length as the first
        int[] secondChunk = new int[firstChunk.length];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print both chunks to verify the copy operation
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk: " + Arrays.toString(secondChunk));
    }
}