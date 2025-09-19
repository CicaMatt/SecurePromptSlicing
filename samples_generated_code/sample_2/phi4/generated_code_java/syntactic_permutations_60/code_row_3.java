import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Print the contents of the buffer
            byte[] bytes = new byte[buffer.remaining()];
            buffer.get(bytes);
            System.out.println(Arrays.toString(bytes));
        } catch (NumberFormatException e) {
            System.err.println("The argument must be a valid integer.");
        }
    }
}