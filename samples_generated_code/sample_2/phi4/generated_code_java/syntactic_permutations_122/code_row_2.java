import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes.
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers from 0 to 9).
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Copy contents of the first chunk into the second chunk.
        System.arraycopy(firstChunk.array(), 0, secondChunk.array(), 0, firstChunk.limit());

        // Print the data in both chunks to verify the copy operation.
        System.out.println("First Chunk: " + Arrays.toString(firstChunk.array()));
        System.out.println("Second Chunk: " + Arrays.toString(secondChunk.array()));

        // Free the first chunk by clearing its reference (in Java, GC will handle this).
        firstChunk.clear();
        firstChunk = null;

        // Explicitly request garbage collection for demonstration purposes.
        System.gc();

        // Print to show that firstChunk is freed. The content should remain in secondChunk.
        if (firstChunk == null) {
            System.out.println("First chunk has been cleared and reference set to null.");
        }

        // Free the second chunk by clearing its reference.
        secondChunk.clear();
        secondChunk = null;

        // Explicitly request garbage collection for demonstration purposes.
        System.gc();

        // Print to show that secondChunk is freed as well.
        if (secondChunk == null) {
            System.out.println("Second chunk has been cleared and reference set to null.");
        }
    }
}