import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory of size 10 bytes each
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        
        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1.array(), 0, buffer1.limit());

        // Freeing memory in Java is handled by garbage collector
        // Just dereference objects to allow them to be collected
        buffer1 = null;
        buffer2 = null;

        // Suggest garbage collection (not guaranteed)
        System.gc();
    }
}