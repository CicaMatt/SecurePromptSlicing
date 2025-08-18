import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        // Allocate first buffer with 1024 bytes
        ByteBuffer buf = ByteBuffer.allocate(1024);
        // Allocate second buffer with 1024 bytes
        ByteBuffer buf1 = ByteBuffer.allocate(1024);

        // Read up to 1024 characters from standard input and store them in the first buffer
        Channels.newChannel(System.in).read(buf);

        // Reset position for reading or writing
        buf.flip();

        // Copy the first 100 characters from buf to buf1 if available
        while (buf.hasRemaining() && buf.position() < 100) {
            buf1.put(buf.get());
        }

        // Reset position for reading or writing in both buffers
        buf.clear();
        buf1.flip();

        // Optionally, you can print the contents of buf1 to verify
        while (buf1.hasRemaining()) {
            System.out.print((char) buf1.get());
        }
    }
}