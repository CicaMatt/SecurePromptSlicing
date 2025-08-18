import java.io.IOException;
import java.nio.ByteBuffer;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        ByteBuffer buf = allocateAndRead(1024);
        ByteBuffer buf1 = allocateAndRead(1024);

        System.out.println("First buffer content: " + new String(buf.array(), 0, buf.position()));
        System.out.println("Second buffer content: " + new String(buf1.array(), 0, buf1.position()));
    }

    private static ByteBuffer allocateAndRead(int size) throws IOException {
        ByteBuffer buffer = ByteBuffer.allocate(size);
        int bytesRead = System.in.read(buffer.array(), 0, Math.min(100, size));
        if (bytesRead > 0) {
            buffer.position(bytesRead);
        }
        return buffer;
    }
}