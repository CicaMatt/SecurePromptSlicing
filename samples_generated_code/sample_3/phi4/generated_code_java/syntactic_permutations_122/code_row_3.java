import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Populate the first chunk with some data (e.g., numbers 0-9)
        for (byte i = 0; i < 10; i++) {
            buffer1.put(i);
        }
        buffer1.flip(); // Switch to reading mode

        // Copy contents of the first chunk into the second chunk
        buffer2.clear();
        buffer1.get(buffer2.array(), buffer1.position(), buffer1.remaining());
        buffer2.flip();

        // Print the contents of the second chunk to verify
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        
        // No explicit freeing is needed in Java for ByteBuffer as it handles garbage collection
    }
}