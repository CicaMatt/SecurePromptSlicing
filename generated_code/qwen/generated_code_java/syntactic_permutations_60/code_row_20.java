import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <buffer_size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < buffer.capacity(); i++) {
                buffer.put((byte) 0); // Initialize with zeros
            }

            buffer.rewind();
            System.out.print("Buffer contents: ");
            while (buffer.hasRemaining()) {
                System.out.printf("%02X ", buffer.get());
            }
            System.out.println();

        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the buffer size.");
        }
    }
}