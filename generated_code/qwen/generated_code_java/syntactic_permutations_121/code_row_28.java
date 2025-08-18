import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        int size = 1024; // Size of the chunks in bytes

        // Allocate first chunk of memory
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(size);

        // Fill the first chunk with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position to the beginning before reading or copying
        buffer1.rewind();

        // Allocate second chunk of memory
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(size);

        // Copy first chunk into second chunk
        buffer2.put(buffer1);

        // Reset the position to the beginning before reading
        buffer2.rewind();

        // Print the contents of the second chunk
        System.out.println("Contents of second chunk after copy:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the first chunk
        buffer1 = null;

        // Print the contents of the second chunk again
        buffer2.rewind();
        System.out.println("Contents of second chunk after freeing first chunk:");
        for (int i = 0; i < size; i++) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Free the memory allocated to the second chunk
        buffer2 = null;
    }
}