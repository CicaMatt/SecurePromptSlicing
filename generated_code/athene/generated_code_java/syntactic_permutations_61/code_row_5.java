import java.nio.Buffer;
import java.nio.ByteBuffer;

public class BufferAllocFree {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = null;

        while (true) {
            buffer = ByteBuffer.allocate(bufferSize);
            buffer.clear(); // Clear the buffer to simulate freeing
        }
    }
}