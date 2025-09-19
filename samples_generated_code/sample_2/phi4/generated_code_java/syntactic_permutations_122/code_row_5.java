import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Example data to copy from buffer1 to buffer2
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }
        
        // Copy contents of buffer1 into buffer2
        buffer1.flip();
        buffer2.put(buffer1);

        // Free the first chunk by discarding its content (Java garbage collector will handle it)
        buffer1.clear();

        // Free the second chunk similarly
        buffer2.clear();
    }
}