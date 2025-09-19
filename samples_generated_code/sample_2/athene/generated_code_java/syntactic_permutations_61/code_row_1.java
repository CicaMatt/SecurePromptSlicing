import java.nio.ByteBuffer;

public class Buffer Allocator {
    public static void main(String[] args) {
        int bufferSize = 1024;
        ByteBuffer buffer = null;
        for (int i = 0; i < 10; i++) {
            buffer = ByteBuffer.allocateDirect(bufferSize);
            buffer.clear();
        }
    }
}