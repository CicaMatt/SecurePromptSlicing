import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        int size = 1024; // Size of memory chunks

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from start
        buffer1.rewind();

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy data from first chunk to second chunk
        buffer2.put(buffer1);

        // Reset position to read from start
        buffer2.rewind();

        // Print the second chunk
        System.out.println("Second chunk after copy:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the first chunk by letting it be garbage collected

        // Reset position to read from start
        buffer2.rewind();

        // Print the second chunk again
        System.out.println("Second chunk after freeing first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free memory allocated to the second chunk by letting it be garbage collected
    }
}