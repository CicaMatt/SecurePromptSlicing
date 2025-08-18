import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with some data for demonstration
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) (i % 256));
            }
            
            buffer.flip();

            System.out.print("Buffer contents: ");
            while (buffer.hasRemaining()) {
                System.out.print(buffer.get() + " ");
            }
        } catch (NumberFormatException e) {
            System.err.println("Error: bufferSize must be a valid integer.");
        }
    }
}