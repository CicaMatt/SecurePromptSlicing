import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            Arrays.fill(buffer, (byte) 0);
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the buffer size.");
            System.exit(1);
        }
    }
}