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

        // Copy contents of the first buffer to the second buffer
        buffer1.flip(); // Prepare buffer1 for reading
        buffer2.put(buffer1);

        // Print the contents of the second buffer
        System.out.println("Contents of the second buffer after copy:");
        buffer2.flip(); // Prepare buffer2 for reading
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
        System.out.println();

        // Clear both buffers to free memory
        buffer1.clear();
        buffer2.clear();
    }
}