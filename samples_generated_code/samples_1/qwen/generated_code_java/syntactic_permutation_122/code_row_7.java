import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Since Java does not have explicit memory management, we just nullify references
        buffer1 = null;
        buffer2 = null;

        // Let the garbage collector handle the memory deallocation
        System.gc();
    }
}