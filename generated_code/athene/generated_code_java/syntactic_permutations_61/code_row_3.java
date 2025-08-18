import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < 10; i++) { // Loop to free the buffer
            buffer.clear(); // Clear the buffer to make it reusable
            buffer = null; // Optionally set to null if you want to allow GC to collect it
            buffer = ByteBuffer.allocate(bufferSize); // Reallocate if needed
        }
    }
}