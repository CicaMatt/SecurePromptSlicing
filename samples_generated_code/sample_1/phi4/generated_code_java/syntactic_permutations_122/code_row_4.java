import java.util.Arrays;

public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        int[] firstChunk = new int[10];
        int[] secondChunk = new int[10];

        // Initialize the first chunk with some values for demonstration
        Arrays.fill(firstChunk, 1);

        // Print contents of the first chunk before copying
        System.out.println("First Chunk Before Copy: " + Arrays.toString(firstChunk));

        // Copy contents of the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print contents of both chunks after copy
        System.out.println("Second Chunk After Copy: " + Arrays.toString(secondChunk));
        
        // Freeing the first chunk by setting it to null (simulated)
        firstChunk = null;

        // Freeing the second chunk by setting it to null (simulated)
        secondChunk = null;
    }
}