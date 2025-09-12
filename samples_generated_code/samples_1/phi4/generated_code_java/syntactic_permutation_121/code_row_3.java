import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each memory chunk
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Copy contents of the first chunk to the second chunk
        firstChunk.flip(); // Switch to reading mode
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }
        
        // Print the contents of the second chunk
        System.out.println("Second chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk
        firstChunk.clear(); // Clear does not free memory, but it resets position and limit

        // Print the contents of the second chunk again
        System.out.println("Second chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk
        secondChunk.clear();
        
        // Attempting to print the second chunk now would result in an error if we try to access its content.
        // Hence, no further action is needed here as clearing ByteBuffer does not free memory but just resets it.

        System.out.println("Memory cleanup done.");
    }
}