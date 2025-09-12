import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Usage: java BufferPrinter <buffer size>");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        byte[] buffer = new byte[bufferSize];

        // Fill the buffer with some arbitrary values for demonstration
        Arrays.fill(buffer, (byte) 1);

        // Print the contents of the buffer
        System.out.println("Buffer contents: " + Arrays.toString(buffer));
    }

    private static boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}