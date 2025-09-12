import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferExample <buffer size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Print the contents of the buffer
            byte[] bufferContents = new byte[buffer.capacity()];
            System.arraycopy(buffer.array(), 0, bufferContents, 0, buffer.capacity());
            System.out.println("Buffer Contents: " + Arrays.toString(bufferContents));
        } catch (NumberFormatException e) {
            System.err.println("Error: Buffer size must be a valid integer.");
            System.exit(1);
        }
    }
}