import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i); // Fill the buffer with incremental byte values
            }
            
            buffer.flip(); // Switch to reading mode

            while (buffer.hasRemaining()) {
                System.out.print(buffer.get() + " ");
            }

        } catch (NumberFormatException e) {
            System.err.println("Error: Buffer size must be a valid integer.");
            System.exit(1);
        }
    }
}