import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset position to start for reading
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.print("Contents of second chunk after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by clearing it
        buffer1.clear();

        // Reset position to start for reading again
        buffer2.rewind();

        // Print the contents of the second chunk (should remain unchanged)
        System.out.print("Contents of second chunk after freeing first: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by clearing it
        buffer2.clear();
    }
}