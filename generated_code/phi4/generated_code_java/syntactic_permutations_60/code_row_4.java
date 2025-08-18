import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Buffer size must be a valid integer.");
            return;
        }

        if (bufferSize <= 0) {
            System.err.println("Buffer size must be greater than zero.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        // Fill the buffer with sample data for demonstration purposes
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) (i % 256)); // Fill with some pattern to visualize
        }
        
        System.out.println("Buffer contents: " + new String(buffer.array(), 0, bufferSize));
    }
}