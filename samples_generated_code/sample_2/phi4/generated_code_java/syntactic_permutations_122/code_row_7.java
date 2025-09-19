import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (for example, numbers 0-9)
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to read from the beginning
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Free the first chunk (ByteBuffer is garbage collected in Java)
        firstChunk = null;

        // Free the second chunk (also eligible for garbage collection)
        secondChunk = null;

        // Suggest JVM to perform garbage collection
        System.gc();
    }
}