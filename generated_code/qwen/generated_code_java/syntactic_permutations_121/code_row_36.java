import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(16);
        ByteBuffer buffer2 = ByteBuffer.allocate(16);

        // Populate the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.println("Contents of buffer2 after copy:");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Reset buffer2 for reading again
        buffer2.flip();

        // Free the memory allocated to the first chunk
        buffer1 = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of buffer2 after freeing buffer1:");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        buffer2 = null;
    }
}