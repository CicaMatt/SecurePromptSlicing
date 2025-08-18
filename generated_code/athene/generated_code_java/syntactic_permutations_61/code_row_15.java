import java.nio.ByteBuffer;

public class BufferManager {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        freeBuffer(buffer);
    }

    private static void freeBuffer(ByteBuffer buffer) {
        ((java.nio.DirectByteBuffer) buffer).cleaner().clean();
    }
}