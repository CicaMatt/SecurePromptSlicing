import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The buffer size must be an integer.");
            return;
        }

        if (bufferSize <= 0) {
            System.out.println("The buffer size must be a positive integer.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        // Fill the buffer with some default values for demonstration
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) i % 256); // Using byte to store values
        }
        
        // Reset position to read from the beginning of the buffer
        buffer.flip();

        System.out.println("Buffer contents: " + Arrays.toString(buffer.array()));
    }
}