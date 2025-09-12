import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer;
        for (int i = 0; i < 10; i++) {
            buffer = ByteBuffer.allocate(1024);
            buffer.clear();
        }
    }
}