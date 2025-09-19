import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Initialize buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset buffer1's position to the beginning before reading
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // "Free" the first chunk by clearing its reference (Java does not have explicit free)
        buffer1 = null;

        // "Free" the second chunk by clearing its reference (Java does not have explicit free)
        buffer2 = null;

        // Suggest to JVM to run garbage collector
        System.gc();
    }
}