import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(16);
        ByteBuffer buffer2 = ByteBuffer.allocate(16);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy data from the first chunk to the second chunk
        buffer2.put(buffer1);

        // Reset position to start before printing
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of the second chunk after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Clear the first chunk (simulating free)
        buffer1.clear();

        // Reset position to start before printing
        buffer2.rewind();

        // Print the contents of the second chunk again
        System.out.print("Contents of the second chunk after freeing the first: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Clear the second chunk (simulating free)
        buffer2.clear();
    }
}