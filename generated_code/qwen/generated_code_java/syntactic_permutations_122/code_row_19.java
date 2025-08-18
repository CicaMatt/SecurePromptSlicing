import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position to read from the beginning
        buffer1.rewind();

        // Copy contents of buffer1 to buffer2
        buffer2.put(buffer1);

        // "Free" buffer1 by letting it be garbage collected
        buffer1 = null;

        // "Free" buffer2 by letting it be garbage collected
        buffer2 = null;

        // Suggest JVM to perform garbage collection
        System.gc();
    }
}