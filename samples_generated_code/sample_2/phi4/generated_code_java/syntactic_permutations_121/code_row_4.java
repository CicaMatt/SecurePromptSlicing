import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate memory for the first chunk
        int[] firstChunk = new int[size];
        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = i + 1;
        }

        // Allocate memory for the second chunk
        int[] secondChunk = new int[size];

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is done implicitly by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (in Java, this is done implicitly by garbage collection)
        secondChunk = null;
    }
}