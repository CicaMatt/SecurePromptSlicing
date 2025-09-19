import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('A' + i));
        }

        // Reset position to read from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Print contents of the second chunk
        System.out.println("Contents of second chunk after copy:");
        buffer2.flip(); // Set limit to current position and position to 0
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        buffer1 = null;

        // Print contents of the second chunk again
        System.out.println("Contents of second chunk after freeing first chunk:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        buffer2 = null;
    }
}