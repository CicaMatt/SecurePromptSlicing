import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents of buffer1 to buffer2
        buffer2.put(buffer1);

        // Reset position to start before reading
        buffer2.rewind();

        // Print the contents of the second buffer
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
    }
}