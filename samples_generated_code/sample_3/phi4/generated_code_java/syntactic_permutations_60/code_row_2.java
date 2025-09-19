import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <buffer-size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.err.println("Error: The provided argument must be an integer.");
            System.exit(1);
        }
    }
}