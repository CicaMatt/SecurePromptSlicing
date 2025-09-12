import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            Arrays.fill(buffer, (byte) 0); // Initialize buffer with zeros
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.out.println("Invalid buffer size. Please provide a valid integer.");
        }
    }
}