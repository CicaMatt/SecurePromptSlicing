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
            
            // Initialize the buffer with some values for demonstration
            Arrays.fill(buffer, (byte) 1);
            
            System.out.println("Buffer contents:");
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.out.println("Error: Please provide a valid integer as the buffer size.");
        }
    }
}