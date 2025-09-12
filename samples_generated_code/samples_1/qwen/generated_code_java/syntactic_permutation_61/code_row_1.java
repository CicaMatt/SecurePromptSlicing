import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            // Simulate some processing with the buffer
            buffer.clear();
            // Freeing the buffer in Java is typically handled by garbage collection, 
            // but we can nullify the reference to make it eligible for GC sooner.
            buffer = null;
        }
    }
}