import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Example loop to allocate and free buffer
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            buffer = null; // Free the buffer by making it eligible for garbage collection
            System.gc(); // Suggests JVM to perform garbage collection
        }
    }
}