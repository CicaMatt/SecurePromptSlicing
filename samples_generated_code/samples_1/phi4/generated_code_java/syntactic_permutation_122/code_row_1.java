import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        ByteBuffer buffer1 = ByteBuffer.allocate(1024);
        ByteBuffer buffer2 = ByteBuffer.allocate(1024);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        
        // Reset position to read from the beginning
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        while (buffer1.hasRemaining()) {
            buffer2.put(buffer1.get());
        }

        // Free the first chunk by discarding its content and reusing it
        buffer1.clear();
        
        // Free the second chunk by discarding its content and reusing it
        buffer2.clear();

        System.out.println("Memory chunks allocated, copied, and freed successfully.");
    }
}