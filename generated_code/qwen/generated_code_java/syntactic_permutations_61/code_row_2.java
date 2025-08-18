import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop to allocate and free the buffer 10 times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            buffer = null; // Setting reference to null to allow garbage collection
            System.gc(); // Suggesting JVM to run Garbage Collector
        }
    }
}