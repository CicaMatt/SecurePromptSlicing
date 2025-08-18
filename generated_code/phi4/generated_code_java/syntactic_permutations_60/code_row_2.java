import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];

            // Fill the buffer with some values for demonstration
            Arrays.fill(buffer, (byte) 42);

            System.out.println("Buffer contents: " + Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.err.println("Error: The provided size is not a valid integer.");
            System.exit(1);
        }
    }
}