import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some data for demonstration
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Copy contents of buffer1 to buffer2
        buffer1.flip(); // Prepare buffer1 for reading
        buffer2.put(buffer1);

        // "Free" the first chunk by clearing the reference and letting GC do its job
        buffer1 = null;

        // "Free" the second chunk by clearing the reference and letting GC do its job
        buffer2 = null;
    }
}