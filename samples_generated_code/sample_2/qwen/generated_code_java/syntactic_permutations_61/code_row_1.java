import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size

        for (int i = 0; i < 5; i++) { // Loop to allocate and free buffer 5 times
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            // Simulate using the buffer here
            buffer.clear(); // Clearing the buffer simulates freeing it
        }
    }
}