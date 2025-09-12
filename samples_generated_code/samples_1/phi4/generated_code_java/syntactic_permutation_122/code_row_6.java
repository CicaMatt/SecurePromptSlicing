import java.nio.ByteBuffer;

public class MemoryManager {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes.
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers 0-9).
        for (byte i = 0; i < 10; i++) {
            buffer1.put(i);
        }
        
        // Copy contents of the first chunk into the second chunk.
        buffer2.put(buffer1.array(), 0, 10);

        // Reset position to read from start
        buffer1.position(0);
        buffer2.position(0);

        // Output the copied data for verification (optional)
        System.out.print("Buffer 2 contents: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        
        System.out.println();

        // Java's ByteBuffer does not require manual deallocation.
        // When the buffers go out of scope, they are eligible for garbage collection.

        // Explicitly clear the buffers to release resources
        buffer1.clear();
        buffer2.clear();
    }
}