import java.nio.ByteBuffer;

public class MemoryManagementExample {

    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill the first chunk with some data for demonstration
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.flip();

        // Copy contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Output copied data to verify
        System.out.println("Copied Data: " + new String(buffer2.array(), 0, buffer2.capacity()));

        // Freeing the first and second chunks
        // Note: In Java, freeing is handled by garbage collection. No explicit free needed.
    }
}