import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[10];

        // Initialize the first chunk with some values
        for (int i = 0; i < 10; i++) {
            chunk1[i] = i + 1;
        }

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, 10);

        // Free the first chunk by setting it to null (Java's garbage collector will handle it)
        chunk1 = null;

        // Print the second chunk to verify contents
        System.out.println("Contents of the second chunk: " + Arrays.toString(chunk2));

        // Free the second chunk by setting it to null
        chunk2 = null;

        // Suggest garbage collection (not guaranteed to run immediately)
        System.gc();
    }
}