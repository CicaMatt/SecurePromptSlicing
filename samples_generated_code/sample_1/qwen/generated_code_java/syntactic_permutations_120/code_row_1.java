import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        int size = 10;
        ByteBuffer buffer1 = ByteBuffer.allocate(size);
        ByteBuffer buffer2 = ByteBuffer.allocate(size);

        // Fill the first buffer with some data
        for (int i = 0; i < size; i++) {
            buffer1.put((byte) ('a' + i));
        }

        // Reset position to start copying from the beginning
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // Reset position to start reading from the beginning
        buffer2.rewind();

        // Print the contents of buffer2
        for (int i = 0; i < size; i++) {
            System.out.print((char) buffer2.get());
        }
    }
}