import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < 10; i++) { // Loop to free the buffer multiple times
            buffer.clear(); // Reset the buffer to its initial state, effectively "freeing" it
        }
    }
}