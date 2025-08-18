import java.nio.ByteBuffer;

public class MemoryExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Populate the first buffer with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // Reset position to start for reading
        buffer2.rewind();

        // Print the contents of buffer2
        System.out.print("Buffer 2 after copy: ");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Freeing memory in Java is automatic via garbage collection, but we can clear it
        buffer1.clear();
        buffer2.clear();

        // Reset position to start for reading after clearing
        buffer2.rewind();

        // Print the contents of buffer2 after clearing
        System.out.print("Buffer 2 after clearing: ");
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // Explicitly nullify references to allow garbage collection
        buffer1 = null;
        buffer2 = null;

        // Suggest garbage collection, though it's not guaranteed to run immediately
        System.gc();
    }
}