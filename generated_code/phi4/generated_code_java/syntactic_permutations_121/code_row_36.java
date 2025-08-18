import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (arrays)
        int[] firstChunk = new int[5];
        int[] secondChunk = new int[5];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Initialize firstChunk with some values for demonstration
        firstChunk[0] = 1;
        firstChunk[1] = 2;
        firstChunk[2] = 3;
        firstChunk[3] = 4;
        firstChunk[4] = 5;

        // Print the contents of secondChunk
        System.out.println("Contents of second chunk after copying: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (set reference to null)
        firstChunk = null;

        // Print the contents of secondChunk again
        System.out.println("Contents of second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to secondChunk (set reference to null)
        secondChunk = null;
    }
}