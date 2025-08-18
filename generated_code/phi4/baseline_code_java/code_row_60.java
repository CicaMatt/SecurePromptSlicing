import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferPrinter <bufferSize>");
            System.exit(1);
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Buffer size must be an integer.");
            System.exit(2);
        }

        if (bufferSize <= 0) {
            System.err.println("Buffer size must be greater than zero.");
            System.exit(3);
        }

        int[] buffer = new int[bufferSize];

        // Fill the buffer with some sample data for demonstration purposes
        Arrays.fill(buffer, -1); // Assigning a default value of -1 to each element

        System.out.println("Buffer contents:");
        System.out.println(Arrays.toString(buffer));
    }
}