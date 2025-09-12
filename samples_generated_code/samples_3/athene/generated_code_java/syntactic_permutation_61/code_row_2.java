import java.nio.ByteBuffer;

public class BufferAllocation {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = null;
        
        while (true) {
            buffer = ByteBuffer.allocateDirect(bufferSize);
            buffer.clear();
        }
    }
}