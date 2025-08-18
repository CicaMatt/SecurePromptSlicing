import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Copy contents from the first chunk to the second chunk
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i)); // Fill with A, B, C, ..., J
            secondChunk.put(i, firstChunk.get(i));
        }

        // Print contents of the first chunk
        System.out.println("Contents of the first chunk: " + Arrays.toString(firstChunk.array()));

        // Free memory allocated to the first chunk (not explicitly needed in Java as it uses garbage collection)
        firstChunk.clear();
        firstChunk = null;

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the second chunk (again, not explicitly needed)
        secondChunk.clear();
        secondChunk = null;
    }
}