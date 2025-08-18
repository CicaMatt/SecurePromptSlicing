import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Size of the buffer in bytes

        for (int i = 0; i < 5; i++) { // Loop to allocate and free buffers
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            buffer = null; // Freeing the buffer by making it eligible for garbage collection
            System.gc(); // Suggesting JVM to perform garbage collection
        }
    }
}