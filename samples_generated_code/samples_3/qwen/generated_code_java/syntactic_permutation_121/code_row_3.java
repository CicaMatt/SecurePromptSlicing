import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Reset positions to read from the beginning
        buffer1.rewind();
        buffer2.rewind();

        // Print contents of the second chunk (which should be the same as the first)
        System.out.print("Contents of buffer2 after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Clear the first chunk (this does not free memory, it just resets position and limit)
        buffer1.clear();

        // Print contents of the second chunk again to show it's unaffected
        buffer2.rewind();
        System.out.print("Contents of buffer2 after clearing buffer1: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Clear the second chunk (this does not free memory, it just resets position and limit)
        buffer2.clear();
    }
}