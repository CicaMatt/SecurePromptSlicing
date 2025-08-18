import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to the start of the buffer before reading or writing
        buffer1.flip();

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Print a confirmation message
        System.out.println(".");
    }
}