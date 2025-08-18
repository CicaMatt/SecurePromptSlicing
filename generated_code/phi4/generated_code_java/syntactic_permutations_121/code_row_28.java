import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory
        int[] chunk1 = new int[10];
        int[] chunk2 = new int[chunk1.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < chunk1.length; i++) {
            chunk1[i] = i + 1;
        }

        // Copy the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length);

        // Print the second chunk
        System.out.println("Second chunk after copying: " + Arrays.toString(chunk2));

        // Free the memory allocated to the first chunk (in Java, this is done automatically by garbage collection)

        // Print the second chunk again
        System.out.println("Second chunk after freeing the first chunk: " + Arrays.toString(chunk2));

        // Free the memory allocated to the second chunk (again, handled by garbage collection)
    }
}