import java.nio.ByteBuffer;

public class MemoryCopy {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each 10 bytes long
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with sample data (e.g., numbers 0-9)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start of buffer1
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset position to start of buffer2 for reading
        buffer2.flip();

        // Print the contents of the second chunk
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
    }
}