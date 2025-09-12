import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = {1, 2, 3, 4, 5};
        int[] secondChunk = new int[firstChunk.length];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Output both chunks to verify the copy
        System.out.println("First Chunk: " + Arrays.toString(firstChunk));
        System.out.println("Second Chunk: " + Arrays.toString(secondChunk));
    }
}