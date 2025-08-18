import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) 'A');
        }
        
        // Reset position to read from the beginning of the buffer if needed
        buffer.flip();
    }
}