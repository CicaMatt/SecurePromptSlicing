import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0-9)
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk
        byte[] firstData = Arrays.copyOf(firstChunk.array(), firstChunk.capacity());
        secondChunk.put(firstData);

        // Print the content of the second chunk
        System.out.println("Second Chunk after copy: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the first chunk by disposing of its reference
        firstChunk = null;

        // Print the content of the second chunk again (should be unchanged)
        System.out.println("Second Chunk after freeing first chunk's memory: " + Arrays.toString(secondChunk.array()));

        // Free the memory allocated to the second chunk by disposing of its reference
        secondChunk = null;
    }
}