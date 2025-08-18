import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk.array(), firstChunk.position(), firstChunk.limit());
        secondChunk.flip();

        // Print the contents of the second chunk
        System.out.println("Contents of the second chunk after copying: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the first chunk (no-op in Java since it's managed by GC)
        firstChunk.clear();
        firstChunk = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of the second chunk after freeing first chunk: " + Arrays.toString(secondChunk.array()));

        // Free memory allocated to the second chunk (no-op in Java since it's managed by GC)
        secondChunk.clear();
        secondChunk = null;

        // Suggest garbage collection, though not guaranteed
        System.gc();
    }
}