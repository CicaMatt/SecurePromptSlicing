import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate two chunks of memory
        byte[] firstChunk = new byte[size];
        byte[] secondChunk = new byte[size];

        // Initialize the first chunk with some values
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) ('A' + i);
        }

        // Copy contents from the first chunk to the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (not explicitly done in Java)
        firstChunk = null;

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk (not explicitly done in Java)
        secondChunk = null;
    }
}