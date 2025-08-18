import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with incremental values for demonstration
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i);
            }
            
            // Convert to array and print contents
            byte[] contentArray = Arrays.copyOf(buffer.array(), bufferSize);
            System.out.println("Buffer Contents: " + Arrays.toString(contentArray));
        } catch (NumberFormatException e) {
            System.err.println("Error: Buffer size must be a valid integer.");
            System.exit(1);
        }
    }
}