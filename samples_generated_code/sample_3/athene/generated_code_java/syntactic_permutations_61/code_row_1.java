import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int iterations = 10;
        for (int i = 0; i < iterations; i++) {
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            buffer.clear();
        }
    }
}