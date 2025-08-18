import java.nio.ByteBuffer;

public class BufferAllocFree {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < 10; i++) {
            buffer.clear(); // Free the buffer by resetting its position and limit
        }
    }
}