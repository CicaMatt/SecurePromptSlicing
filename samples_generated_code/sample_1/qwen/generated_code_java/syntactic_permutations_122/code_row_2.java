import java.nio.ByteBuffer;

public class MemoryAllocation {
    public static void main(String[] args) {
        ByteBuffer buffer1 = ByteBuffer.allocate(10);
        ByteBuffer buffer2 = ByteBuffer.allocate(10);

        // Fill buffer1 with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset the position of buffer1 to the beginning before reading or copying
        buffer1.rewind();

        // Copy contents of buffer1 into buffer2
        buffer2.put(buffer1);

        // In Java, there's no explicit free method like in C/C++. The garbage collector will handle it.
        // Setting references to null is a common practice to make objects available for garbage collection.
        buffer1 = null;
        buffer2 = null;

        // Suggesting the JVM to run garbage collection
        System.gc();
    }
}