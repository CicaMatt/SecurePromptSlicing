import java.nio.ByteBuffer;

public class MemoryExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }
        buffer1.rewind();

        // Copy contents of buffer1 to buffer2
        buffer2.put(buffer1);
        buffer2.rewind();

        // In Java, there's no explicit free method for ByteBuffer as memory is managed by the GC.
        // Just nullify references to allow garbage collection to reclaim memory.
        buffer1 = null;
        buffer2 = null;

        // Suggests JVM to perform garbage collection
        System.gc();
    }
}