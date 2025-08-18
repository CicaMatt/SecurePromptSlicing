import java.nio.ByteBuffer;

public class MemoryCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory with 10 bytes each
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (e.g., numbers from 0 to 9)
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk: ");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
    }
}