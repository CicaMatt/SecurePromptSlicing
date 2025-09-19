import java.nio.ByteBuffer;

public class MemoryManagementExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Fill the first buffer with some data
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start copying from the beginning
        buffer1.rewind();

        // Copy the contents of the first buffer into the second buffer
        buffer2.put(buffer1);

        // Free the first chunk (ByteBuffer does not have an explicit free method in Java)
        // The garbage collector will eventually reclaim the memory when there are no more references
        buffer1 = null;

        // Free the second chunk
        buffer2 = null;

        // Suggest to the JVM that it can run the garbage collector
        System.gc();
    }
}