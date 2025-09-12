import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (for demonstration purposes)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Copy contents of the first chunk into the second
        buffer2.put(buffer1.array(), 0, buffer1.position());

        // Free the first chunk by letting it go out of scope
        buffer1 = null;

        // Explicitly request garbage collection (optional and not guaranteed)
        System.gc();

        // Free the second chunk by letting it go out of scope
        buffer2 = null;

        // Explicitly request garbage collection again (optional and not guaranteed)
        System.gc();
    }
}