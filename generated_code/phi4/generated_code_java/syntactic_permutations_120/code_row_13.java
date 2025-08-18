import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (buffers)
        ByteBuffer firstChunk = ByteBuffer.allocate(16);  // First chunk with 16 bytes
        ByteBuffer secondChunk = ByteBuffer.allocate(16); // Second chunk with 16 bytes

        // Fill the first chunk with some data (e.g., numbers from 0 to 15)
        for (int i = 0; i < firstChunk.capacity(); i++) {
            firstChunk.put((byte) i);
        }
        
        firstChunk.flip(); // Prepare buffer for reading
        
        // Copy contents of the first chunk into the second chunk
        secondChunk.put(firstChunk);

        // Print the contents of the second chunk
        secondChunk.flip(); // Prepare buffer for reading
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
    }
}