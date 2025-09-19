import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Fill the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 2;
        }

        // Copy contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));
    }
}