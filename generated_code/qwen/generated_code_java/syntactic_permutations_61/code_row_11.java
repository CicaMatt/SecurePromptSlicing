import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop to allocate and free the buffer multiple times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate using the buffer here
            buffer = null; // Freeing the buffer by making it eligible for garbage collection
            System.gc(); // Suggesting JVM to perform garbage collection
        }
    }
}