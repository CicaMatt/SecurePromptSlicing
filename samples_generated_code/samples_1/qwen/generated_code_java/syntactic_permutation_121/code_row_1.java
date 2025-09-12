import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int size = 1024; // Size of each memory chunk in bytes

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocate(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Copy data from first chunk to second chunk
        buffer2.put(buffer1);

        // Reset position to start reading from the beginning
        buffer2.rewind();

        // Print the second chunk
        System.out.println("Second chunk after copy:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by setting it to null
        buffer1 = null;

        // Print the second chunk again
        buffer2.rewind();
        System.out.println("Second chunk after freeing first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by setting it to null
        buffer2 = null;
    }
}