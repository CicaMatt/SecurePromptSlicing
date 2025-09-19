import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            System.exit(1);
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Buffer size must be an integer.");
            System.exit(2);
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Fill the buffer with example values to show its contents
        for (int i = 0; i < bufferSize && buffer.hasRemaining(); i++) {
            buffer.put((byte) i); // Simple example: filling buffer with increasing byte values
        }

        System.out.println("Buffer Contents: " + Arrays.toString(buffer.array()));
    }
}