import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagement {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Example size
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Initialize the first chunk with some data
        for (int i = 0; i < size; i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip(); // Prepare the buffer for reading

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        secondChunk.flip();
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the first chunk (simulated by reusing ByteBuffer)
        firstChunk.clear();

        // Print the contents of the second chunk again
        System.out.println("Second Chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the second chunk (simulated by reusing ByteBuffer)
        secondChunk.clear();
    }
}