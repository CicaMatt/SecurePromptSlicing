import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            buffer1.put((byte) (i + 65)); // Fill with ASCII values for A-J
        }

        buffer1.rewind(); // Reset position to the beginning of the buffer
        buffer2.put(buffer1); // Copy contents from buffer1 to buffer2

        buffer2.rewind(); // Reset position to the beginning of the buffer
        while (buffer2.hasRemaining()) {
            System.out.print((char) buffer2.get()); // Print contents of buffer2
        }
    }
}