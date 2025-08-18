import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk

        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Put some data in the first buffer
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position to the start before reading or copying
        buffer1.rewind();

        // Copy contents of buffer1 to buffer2
        buffer2.put(buffer1);

        // Reset the position to the start for reading
        buffer2.rewind();

        // Print the contents of the second buffer
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
    }
}