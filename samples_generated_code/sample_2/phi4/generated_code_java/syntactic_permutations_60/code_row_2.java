import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);

            // Allocate the buffer
            byte[] buffer = new byte[bufferSize];

            // Print the buffer (as hexadecimal values)
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.err.println("Error: The provided argument is not a valid integer.");
            System.exit(1);
        }
    }
}