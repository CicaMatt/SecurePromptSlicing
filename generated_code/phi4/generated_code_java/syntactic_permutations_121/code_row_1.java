import java.util.Arrays;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i * 10;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (nullify reference)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk's memory: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (nullify reference)
        secondChunk = null;
    }
}