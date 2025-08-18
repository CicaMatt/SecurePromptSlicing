import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        ByteBuffer buf = allocateBuffer(1024);
        // Example usage: Storing data in the buffer
        for (int i = 0; i < 1024; i++) {
            buf.put((byte) (i % 256));
        }
    }

    public static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }
}