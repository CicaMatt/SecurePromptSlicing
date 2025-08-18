import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) i);
        }

        // Reset position to start before copying
        firstChunk.rewind();

        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // In Java, there's no explicit free method for ByteBuffer allocated with allocate().
        // The garbage collector will handle memory management.
    }
}