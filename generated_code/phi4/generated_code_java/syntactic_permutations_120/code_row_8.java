import java.nio.ByteBuffer;

public class MemoryCopyExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip();

        // Copy contents from the first chunk to the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print the contents of the second chunk
        secondChunk.flip();
        while (secondChunk.hasRemaining()) {
            System.out.print((char) secondChunk.get() + " ");
        }
    }
}