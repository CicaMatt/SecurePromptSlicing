import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop to allocate and free the buffer
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            buffer = null; // Freeing the buffer by dereferencing it
            System.gc(); // Suggesting JVM to garbage collect, though not guaranteed to run immediately
        }
    }
}