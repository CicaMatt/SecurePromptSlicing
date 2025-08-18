import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int[] firstChunk = {1, 2, 3, 4, 5};
        int[] secondChunk = new int[firstChunk.length];

        // Copy contents from the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    }
}