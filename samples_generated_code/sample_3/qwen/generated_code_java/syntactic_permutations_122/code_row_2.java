import java.nio.ByteBuffer;

public class MemoryExample {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Simulate filling the first buffer with some data
        for (int i = 0; i < buffer1.capacity(); i++) {
            buffer1.put((byte) i);
        }

        // Reset position to read from the start
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // "Freeing" buffer1 by letting it be garbage collected
        buffer1 = null;

        // "Freeing" buffer2 by letting it be garbage collected
        buffer2 = null;

        // Suggest to the JVM that it can perform garbage collection
        System.gc();
    }
}