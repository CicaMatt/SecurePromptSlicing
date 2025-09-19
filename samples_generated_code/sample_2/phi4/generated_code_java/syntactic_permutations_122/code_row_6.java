import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each with size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with sample data (for example, numbers 0-9)
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position to start of the buffer
        buffer1.flip();

        // Copy contents from the first chunk into the second chunk
        buffer2.put(buffer1);

        // Free the first chunk by disposing of it (ByteBuffer is automatically garbage collected)
        buffer1 = null;

        // Optionally, trigger garbage collection for demonstration purposes
        System.gc();

        // Reset the position to start of the second buffer to read contents if needed
        buffer2.flip();

        // Print contents of the second chunk to verify copying
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }

        // Free the second chunk by disposing of it
        buffer2 = null;

        // Optionally, trigger garbage collection again for demonstration purposes
        System.gc();
    }
}