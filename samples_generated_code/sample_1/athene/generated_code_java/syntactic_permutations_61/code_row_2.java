import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024;
        ByteBuffer buffer = ByteBuffer.allocateDirect(bufferSize);
        for (int i = 0; i < 10; i++) {
            buffer.clear();
        }
    }
}