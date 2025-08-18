import java.nio.ByteBuffer;

public class Buffer Allocator {
    private ByteBuffer buffer;

    public BufferAllocator(int bufferSize) {
        this.buffer = ByteBuffer.allocate(bufferSize);
    }

    public void freeBufferInLoop(int iterations) {
        for (int i = 0; i < iterations; i++) {
            buffer.clear();
        }
    }

    public static void main(String[] args) {
        int bufferSize = 1024;
        int iterations = 10;
        BufferAllocator allocator = new BufferAllocator(bufferSize);
        allocator.freeBufferInLoop(iterations);
    }
}