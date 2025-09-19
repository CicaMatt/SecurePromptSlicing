import java.nio.ByteBuffer;

public class MemoryManagement {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from the beginning
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // In Java, ByteBuffer does not require explicit free.
        // The garbage collector will handle memory management.
    }
}