import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        ByteBuffer buf = allocateBuffer(1024);
        
        byte[] readBuffer = new byte[10];
        int bytesRead = System.in.read(readBuffer, 0, 10);

        if (bytesRead > 0) {
            buf.put(readBuffer, 0, bytesRead);
        }

        // Print the buffer content for verification
        System.out.println(new String(buf.array(), 0, bytesRead));
    }

    private static ByteBuffer allocateBuffer(int size) {
        return ByteBuffer.allocate(size);
    }
}