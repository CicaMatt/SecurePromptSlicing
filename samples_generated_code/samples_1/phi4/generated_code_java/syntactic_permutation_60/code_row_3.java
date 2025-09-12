import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            
            // Fill the buffer with example data for demonstration
            Arrays.fill(buffer, (byte) 42); // Fill with arbitrary value

            System.out.println("Buffer contents:");
            for (byte b : buffer) {
                System.out.print(b + " ");
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: Argument must be a valid integer.");
        }
    }
}