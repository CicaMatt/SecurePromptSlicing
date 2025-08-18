import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        
        for (int i = 0; i < 10; i++) { // Loop 10 times to simulate freeing the buffer
            buffer.clear(); // Reset the buffer position and limit, effectively "freeing" it for reuse
        }
    }
}