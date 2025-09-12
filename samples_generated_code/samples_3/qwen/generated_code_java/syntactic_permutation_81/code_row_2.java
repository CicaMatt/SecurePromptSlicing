import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = allocateBuffer();
        byte[] buf = new byte[buffer.capacity()];
        buffer.get(buf);
    }

    public static ByteBuffer allocateBuffer() {
        return ByteBuffer.allocate(1024);
    }
}