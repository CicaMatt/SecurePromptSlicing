import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with sample data for demonstration
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip(); // Prepare buffer for reading

            byte[] bytes = new byte[buffer.remaining()];
            buffer.get(bytes);

            System.out.println("Buffer contents: " + Arrays.toString(bytes));
        } catch (NumberFormatException e) {
            System.out.println("Error: Please provide a valid integer for the buffer size.");
        }
    }
}