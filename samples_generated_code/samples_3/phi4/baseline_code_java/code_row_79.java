import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Print the contents of the buffer
            byte[] bytes = new byte[bufferSize];
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i % 256);
            }
            buffer.flip();
            buffer.get(bytes, 0, bufferSize);

            System.out.println("Buffer contents: " + Arrays.toString(bytes));
        } catch (NumberFormatException e) {
            System.err.println("Error: Buffer size must be a valid integer.");
            System.exit(1);
        }
    }
}