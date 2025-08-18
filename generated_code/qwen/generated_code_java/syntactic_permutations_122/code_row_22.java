import java.nio.ByteBuffer;

public class MemoryCopyExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill buffer1 with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        buffer1.flip();

        // Copy contents of buffer1 to buffer2
        buffer2.put(buffer1);

        // Free the second chunk by clearing it
        buffer2.clear();
    }
}