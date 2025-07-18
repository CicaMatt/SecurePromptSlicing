import java.nio.ByteBuffer;

public class MemoryAllocator {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
        byte[] buf = new byte[1024];
        buffer.put(buf);
    }
}