import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to the beginning before reading
        buffer1.rewind();

        // Copy contents from buffer1 to buffer2
        buffer2.put(buffer1);

        // In Java, there's no explicit way to free memory like in C/C++
        // The garbage collector will eventually handle it when the buffers are no longer referenced
        buffer1 = null;
        buffer2 = null;

        // Suggesting the JVM to run garbage collection
        System.gc();
    }
}