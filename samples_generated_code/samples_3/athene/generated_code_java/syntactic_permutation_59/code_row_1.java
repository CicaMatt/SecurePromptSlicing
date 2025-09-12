import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        char fillChar = 'A';
        
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) fillChar);
        }
    }
}