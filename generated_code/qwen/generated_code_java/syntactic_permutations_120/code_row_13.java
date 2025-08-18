import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Put some data into the first buffer
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Reset the position of buffer1 to the beginning before copying
        buffer1.flip();

        // Copy data from buffer1 to buffer2
        buffer2.put(buffer1);

        // Reset the position of buffer2 to the beginning before reading
        buffer2.flip();

        // Print the contents of the second buffer
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
    }
}