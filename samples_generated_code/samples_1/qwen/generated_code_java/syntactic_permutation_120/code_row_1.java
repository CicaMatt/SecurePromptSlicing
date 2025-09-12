import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill buffer1 with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start before copying
        buffer1.rewind();

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // Reset position to start for printing
        buffer2.rewind();

        // Print contents of buffer2
        while (buffer2.hasRemaining()) {
            System.out.print(buffer2.get() + " ");
        }
    }
}