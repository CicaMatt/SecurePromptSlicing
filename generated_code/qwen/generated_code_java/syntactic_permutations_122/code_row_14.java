import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory, each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Put some data into the first buffer for demonstration
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Rewind buffer1 to read from the beginning
        buffer1.rewind();

        // Copy data from buffer1 to buffer2
        buffer2.put(buffer1);

        // In Java, there's no explicit free method. The garbage collector will handle it.
        // However, we can help by explicitly clearing references and calling gc().
        buffer1 = null;
        System.gc();

        // Similarly, clear the reference for buffer2 and suggest garbage collection
        buffer2 = null;
        System.gc();
    }
}