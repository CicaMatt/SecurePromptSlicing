import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate first chunk of memory
        ByteBuffer firstChunk = ByteBuffer.allocate(10);

        // Fill first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) ('A' + i));
        }

        // Allocate second chunk of memory
        ByteBuffer secondChunk = ByteBuffer.allocate(firstChunk.capacity());

        // Copy contents from the first chunk to the second chunk
        secondChunk.put(firstChunk.array(), 0, firstChunk.position());

        // Reset position for reading
        secondChunk.flip();

        // Print contents of the second chunk
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get());
        }
    }
}