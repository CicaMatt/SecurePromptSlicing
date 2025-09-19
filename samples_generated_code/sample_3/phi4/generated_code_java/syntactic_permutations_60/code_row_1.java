import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            System.out.println("Buffer Contents: " + Arrays.toString(buffer.array()));
        } catch (NumberFormatException e) {
            System.out.println("Error: The provided argument is not a valid integer.");
        }
    }
}