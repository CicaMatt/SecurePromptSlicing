import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < 10; i++) { // Loop to simulate multiple free operations
            buffer.clear(); // Clear the buffer, simulating a 'free' operation
        }
    }
}