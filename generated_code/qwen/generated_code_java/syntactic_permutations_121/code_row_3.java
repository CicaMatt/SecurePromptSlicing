import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 16; // Size of each memory chunk in bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to start reading from the beginning
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // Reset the position of buffer2 to start reading from the beginning
        buffer2.rewind();

        // Print the contents of buffer2
        System.out.print("Contents of second chunk after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to buffer1 by nullifying it and calling garbage collector
        buffer1 = null;
        System.gc();

        // Reset the position of buffer2 to start reading from the beginning again
        buffer2.rewind();

        // Print the contents of buffer2
        System.out.print("Contents of second chunk after freeing first chunk: ");
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to buffer2 by nullifying it and calling garbage collector
        buffer2 = null;
        System.gc();
    }
}