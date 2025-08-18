import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (byte arrays)
        byte[] firstChunk = new byte[10];
        byte[] secondChunk = new byte[firstChunk.length];

        // Initialize the first chunk with some values
        for (int i = 0; i < firstChunk.length; i++) {
            firstChunk[i] = (byte) (i + 65); // ASCII values for 'A' to 'J'
        }

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(firstChunk, 0, secondChunk, 0, firstChunk.length);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copy: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the first chunk by setting it to null
        firstChunk = null;

        // Print the contents of the second chunk (should remain unchanged)
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk));

        // Free the memory allocated to the second chunk by setting it to null
        secondChunk = null;

        // Note: In Java, memory management is handled by the garbage collector,
        // so there's no explicit way to free memory like in C/C++.
        // Setting references to null helps the garbage collector reclaim memory.
    }
}