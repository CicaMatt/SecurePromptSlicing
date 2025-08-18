import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.flip();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);
        buffer2.flip();

        // Print the contents of the second chunk
        System.out.print("Contents of buffer2 after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();
        buffer2.rewind();

        // Free the memory allocated to the first chunk
        // Note: Direct buffers in Java are automatically freed by garbage collector, but we can help it
        buffer1 = null;

        // Print the contents of the second chunk again
        System.out.print("Contents of buffer2 after freeing buffer1: ");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();
    }
}