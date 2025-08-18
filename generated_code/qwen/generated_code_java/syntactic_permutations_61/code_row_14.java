import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        buffer = null; // Effectively "freeing" the buffer by dereferencing it
        System.gc(); // Suggesting JVM to perform garbage collection, though not guaranteed
    }
}