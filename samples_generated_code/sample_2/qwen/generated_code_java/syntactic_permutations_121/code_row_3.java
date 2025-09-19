import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 10;
        
        // Allocate first chunk of memory
        byte[] firstChunk = new byte[size];
        for (int i = 0; i < size; i++) {
            firstChunk[i] = (byte) (i + 65); // Fill with ASCII values for A to J
        }

        // Allocate second chunk of memory
        byte[] secondChunk = new byte[size];

        // Copy contents from first chunk to second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, size);

        // Print contents of the second chunk
        System.out.println("Contents of second chunk after copy: " + Arrays.toString(secondChunk));

        // Free memory allocated to the first chunk (Java handles this automatically)
        firstChunk = null;

        // Print contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free memory allocated to the second chunk (Java handles this automatically)
        secondChunk = null;
    }
}