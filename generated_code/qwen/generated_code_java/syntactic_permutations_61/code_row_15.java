import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        // In Java, there's no explicit "free" method for buffers.
        // The garbage collector will reclaim the memory when it's no longer reachable.
        buffer = null; // Making buffer unreachable to allow GC to collect it
    }
}