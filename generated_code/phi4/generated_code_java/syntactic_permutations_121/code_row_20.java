import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        int[] firstChunk = new int[10];  // First chunk with size 10
        int[] secondChunk;                // Second chunk to be allocated

        // Copy some sample data into the first chunk
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = i + 1;
        }

        // Allocate memory for the second chunk and copy contents from the first chunk
        secondChunk = Arrays.copyOf(firstChunk, firstChunk.length);

        // Print the contents of the second chunk after copying
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk (in Java, this is handled by garbage collection)
        firstChunk = null;

        // Print the contents of the second chunk before freeing its memory
        System.out.println("Contents of the second chunk before freeing: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk (again, in Java, this is handled by garbage collection)
        secondChunk = null;

        // Suggest to the JVM to perform garbage collection
        System.gc();

        // End of program
    }
}