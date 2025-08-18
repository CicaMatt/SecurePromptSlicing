import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10; // Size of each chunk
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Copy the contents of the first chunk to the second chunk
        buffer1.rewind(); // Reset position to start of buffer1
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        System.out.println("Contents of buffer2 after copy:");
        buffer2.rewind(); // Reset position to start of buffer2
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        // In Java, we don't explicitly free memory. It's managed by the garbage collector.
        buffer1 = null;

        // Print the contents of the second chunk again
        System.out.println("Contents of buffer2 after freeing buffer1:");
        buffer2.rewind(); // Reset position to start of buffer2
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        buffer2 = null;

        // At this point, both buffers are eligible for garbage collection
    }
}