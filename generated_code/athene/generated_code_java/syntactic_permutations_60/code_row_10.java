import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: BufferAllocator <size>");
            System.exit(1);
        }
        
        int size = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(size);

        for (int i = 0; i < size; i++) {
            buffer.put((byte) i); // Fill with some content
        }

        buffer.rewind(); // Reset position to start of the buffer

        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}