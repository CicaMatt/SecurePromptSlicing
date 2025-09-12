import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 10; i++) { // Loop to allocate and free the buffer multiple times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize); // Allocate buffer
            buffer = null; // Free buffer by setting reference to null
            System.gc(); // Suggest garbage collection, though not guaranteed to run immediately
        }
    }
}