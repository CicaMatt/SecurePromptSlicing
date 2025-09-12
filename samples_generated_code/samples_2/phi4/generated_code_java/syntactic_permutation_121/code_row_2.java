import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int[] firstChunk = new int[5];  // First chunk with size 5
        int[] secondChunk = new int[5]; // Second chunk with size 5

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk before freeing first chunk
        System.out.println("Contents of the second chunk (before freeing first): " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk by setting it to null
        firstChunk = null;

        // Print the contents of the second chunk after freeing first chunk
        System.out.println("Contents of the second chunk (after freeing first): " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk by setting it to null
        secondChunk = null;
    }
}