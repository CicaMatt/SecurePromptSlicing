import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (buffers)
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) ('A' + i));
        }
        firstChunk.flip(); // Switch to reading mode

        // Copy contents of the first chunk into the second chunk
        while (firstChunk.hasRemaining()) {
            secondChunk.put(firstChunk.get());
        }

        // Print the contents of the second chunk
        secondChunk.flip(); // Switch to reading mode for printing
        byte[] array = new byte[secondChunk.capacity()];
        secondChunk.get(array);
        
        System.out.println(new String(array));
    }
}