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

        // Copy the first chunk into the second chunk
        buffer1.flip();
        buffer2.put(buffer1);

        // Print the second chunk
        System.out.println("Second chunk after copy:");
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // "Free" the memory allocated to the first chunk by clearing it
        buffer1.clear();

        // Print the second chunk again
        System.out.println("Second chunk after 'freeing' first chunk:");
        buffer2.flip();
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
        System.out.println();

        // "Free" the memory allocated to the second chunk by clearing it
        buffer2.clear();
    }
}