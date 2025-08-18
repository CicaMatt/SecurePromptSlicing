import java.nio.ByteBuffer;
import java.util.Arrays;

public class ByteBufferExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java ByteBufferExample <buffer size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with some sample data for demonstration
            for (int i = 0; i < bufferSize && i < 256; i++) { // Limit to byte range for illustration
                buffer.put((byte) i);
            }

            System.out.println("Buffer Contents: " + Arrays.toString(buffer.array()));

        } catch (NumberFormatException e) {
            System.out.println("Invalid number format. Please provide an integer for the buffer size.");
        }
    }
}