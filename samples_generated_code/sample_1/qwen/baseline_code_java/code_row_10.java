import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (using ByteBuffer for demonstration)
        int size = 10; // Size of the memory chunks
        ByteBuffer firstChunk = ByteBuffer.allocate(size);
        ByteBuffer secondChunk = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        byte[] data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        firstChunk.put(data);

        // Copy the contents of the first chunk into the second chunk
        firstChunk.rewind(); // Reset position to the beginning before reading
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk.array()));

        // In Java, memory is managed by the garbage collector, so we don't explicitly free memory.
        // However, to simulate freeing the first chunk, we can clear its reference and reset it.
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after 'freeing' the first chunk: " + Arrays.toString(secondChunk.array()));

        // To simulate freeing the second chunk, we can clear its reference and reset it.
        secondChunk = null;
    }
}