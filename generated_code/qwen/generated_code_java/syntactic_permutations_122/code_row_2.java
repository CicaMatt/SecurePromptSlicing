import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data (for demonstration purposes)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset buffer1's position to start reading from the beginning
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // In Java, there is no explicit free operation.
        // The garbage collector will handle memory management.
        // To simulate freeing, we just let the buffers go out of scope.
    }
}