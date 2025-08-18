import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferAllocator <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) 0);
            }

            buffer.rewind();

            StringBuilder contents = new StringBuilder();
            while (buffer.hasRemaining()) {
                contents.append(String.format("%02X ", buffer.get()));
            }

            System.out.println(contents.toString().trim());
        } catch (NumberFormatException e) {
            System.err.println("Invalid buffer size: " + args[0]);
            System.exit(1);
        }
    }
}