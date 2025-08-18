import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Print the contents of the buffer
            byte[] array = new byte[buffer.remaining()];
            buffer.get(array);
            System.out.println("Buffer contents: " + Arrays.toString(array));
        } catch (NumberFormatException e) {
            System.err.println("Error: The provided argument is not a valid integer.");
            System.exit(1);
        }
    }
}