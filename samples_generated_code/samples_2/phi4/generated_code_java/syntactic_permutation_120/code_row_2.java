import java.nio.ByteBuffer;
import java.util.Arrays;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each with 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        byte[] dataToCopy = new byte[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        buffer1.put(dataToCopy);

        // Reset position to read from the start of the buffer
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        while (buffer1.hasRemaining()) {
            byte b = buffer1.get();
            buffer2.put(b);
        }

        // Verify by printing both buffers
        System.out.println("Buffer 1: " + Arrays.toString(buffer1.array()));
        System.out.println("Buffer 2: " + Arrays.toString(buffer2.array()));

        // Reset position of buffer2 to read from the start for further operations
        buffer2.flip();
    }
}