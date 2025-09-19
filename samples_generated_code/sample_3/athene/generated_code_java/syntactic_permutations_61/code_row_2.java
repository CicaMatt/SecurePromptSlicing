import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        
        for (int i = 0; i < 10; i++) { // Loop to free the buffer
            buffer.clear(); // Clear the buffer to reuse or free memory
        }
    }
}