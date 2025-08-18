import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int size = 16; // Size of each chunk in bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Copy the contents of the first chunk into the second chunk
        buffer1.rewind(); // Rewind buffer1 to the beginning before reading
        buffer2.put(buffer1);

        // Print the contents of the second chunk
        buffer2.rewind(); // Rewind buffer2 to the beginning before reading
        System.out.println("Contents of the second chunk after copy:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // In Java, memory is managed by the garbage collector, so we don't explicitly free it.
        // However, we can clear the buffers to indicate they are no longer in use.
        buffer1.clear();
        buffer2.clear();

        // Print the contents of the second chunk after clearing
        buffer2.rewind(); // Rewind buffer2 to the beginning before reading
        System.out.println("Contents of the second chunk after clearing:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Note: In practice, we don't need to explicitly free memory in Java.
        // The garbage collector will handle it when the buffers go out of scope.
    }
}