import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10; // Size of each memory chunk

        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('A' + i));
        }
        buffer1.flip(); // Prepare buffer for reading

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Print the contents of the second buffer
        buffer2.flip(); // Prepare buffer for reading
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get());
        }
    }
}