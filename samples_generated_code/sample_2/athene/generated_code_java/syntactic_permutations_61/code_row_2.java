import java.nio.Buffer;
import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < 5; i++) { // Loop to free the buffer multiple times
            buffer.clear(); // Reset the buffer, effectively freeing it for reuse
        }
    }
}