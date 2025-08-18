import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory each of size 10 bytes
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(10);
        ByteBuffer buffer2 = ByteBuffer.allocateDirect(10);

        // Put some data into the first chunk
        for (int i = 0; i < 10; i++) {
            buffer1.put((byte) i);
        }

        // Reset position to start reading from the beginning
        buffer1.rewind();

        // Copy the contents of the first chunk into the second chunk
        buffer2.put(buffer1);

        // Freeing memory in Java is handled by the garbage collector, 
        // but we can nullify references to make objects eligible for garbage collection
        buffer1 = null;
        buffer2 = null;

        // Suggests JVM to run Garbage Collector
        System.gc();
    }
}