import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second
        buffer2.put(buffer1);

        // Free the first chunk by setting its reference to null
        buffer1 = null;

        // Free the second chunk by setting its reference to null
        buffer2 = null;
    }
}