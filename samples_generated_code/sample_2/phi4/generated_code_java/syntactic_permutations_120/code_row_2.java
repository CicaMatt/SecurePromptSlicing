import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each 10 bytes long
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('A' + i));
        }

        // Reset the position of buffer1 to read from the beginning
        buffer1.flip();

        // Copy contents of the first chunk to the second chunk
        buffer2.put(buffer1);

        // Reset the position of buffer2 to read from the beginning
        buffer2.flip();

        // Print the contents of the second chunk
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
    }
}