import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        while (true) {
            buffer.clear();
        }
    }
}