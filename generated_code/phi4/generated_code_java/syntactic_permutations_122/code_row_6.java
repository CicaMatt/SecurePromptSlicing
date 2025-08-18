import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate first chunk of size 10
        ByteBuffer firstChunk = ByteBuffer.allocate(10);
        
        // Fill the first chunk with some data (e.g., numbers 0-9)
        for (byte i = 0; i < 10; i++) {
            firstChunk.put(i);
        }
        
        // Allocate second chunk of size 10
        ByteBuffer secondChunk = ByteBuffer.allocate(10);

        // Copy contents from the first chunk to the second chunk
        firstChunk.flip(); // Prepare the buffer for reading
        secondChunk.clear();
        secondChunk.put(firstChunk);
        secondChunk.flip();

        // Print the content of the second chunk to verify
        while (secondChunk.hasRemaining()) {
            System.out.print(secondChunk.get() + " ");
        }
        
        System.out.println();

        // Freeing chunks is automatic with ByteBuffer, no explicit free needed.
    }
}