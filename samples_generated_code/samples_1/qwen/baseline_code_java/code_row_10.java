import java.nio.ByteBuffer;

public class MemoryAllocationAndCopy {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to the start before copying
        buffer1.rewind();

        // Copy contents from the first chunk to the second chunk
        buffer2.put(buffer1);

        // Print contents of the second chunk
        System.out.println("Contents of the second chunk after copy:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Freeing memory in Java is handled by the garbage collector, so we clear buffers
        buffer1.clear(); // Clearing buffer1

        // Print contents of the second chunk again
        System.out.println("Contents of the second chunk after clearing first:");
        buffer2.rewind();
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Freeing memory in Java is handled by the garbage collector, so we clear buffers
        buffer2.clear(); // Clearing buffer2
    }
}