import java.util.Arrays;

public class MemoryManagement {
    public static void main(String[] args) {
        int size = 5;
        
        // Allocate memory for the first chunk
        int[] firstChunk = new int[size];
        Arrays.fill(firstChunk, 1);  // Fill with some values

        // Allocate memory for the second chunk
        int[] secondChunk = new int[size];

        // Copy contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (in Java, this is handled by garbage collector)
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing the first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk
        secondChunk = null;
        
        // Suggest garbage collection (not guaranteed)
        System.gc();
    }
}