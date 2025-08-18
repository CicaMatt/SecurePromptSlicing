import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes.
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0-9).
        for (int i = 0; i < 10; i++) {
            firstChunk.put((byte) i);
        }
        
        // Reset the position to zero before copying.
        firstChunk.flip();

        // Copy contents of the first chunk into the second chunk.
        secondChunk.clear();
        secondChunk.put(firstChunk);

        // Free the first chunk (simulated by reusing the ByteBuffer object).
        firstChunk = null;

        // Free the second chunk (simulated by reusing the ByteBuffer object).
        secondChunk = null;

        // Suggest garbage collection
        System.gc();

        // Note: In Java, memory management and garbage collection are handled automatically.
    }
}