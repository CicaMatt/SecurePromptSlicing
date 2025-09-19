import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory (byte buffers)
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first buffer with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
    }
}