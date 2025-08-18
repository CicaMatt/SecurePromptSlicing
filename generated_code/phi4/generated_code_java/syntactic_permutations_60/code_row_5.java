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
            
            if (bufferSize <= 0) {
                throw new IllegalArgumentException("Buffer size must be a positive integer.");
            }
        } catch (NumberFormatException e) {
            System.err.println("Error: Buffer size must be an integer.");
            System.exit(1);
            return;
        } catch (IllegalArgumentException e) {
            System.err.println(e.getMessage());
            System.exit(1);
            return;
        }

        byte[] buffer = new byte[bufferSize];
        
        // Initialize the buffer with sample values for demonstration
        Arrays.fill(buffer, (byte) 0xAB);

        // Print contents of the buffer as hex strings
        StringBuilder sb = new StringBuilder();
        for (byte b : buffer) {
            sb.append(String.format("%02X ", b));
        }
        System.out.println("Buffer Contents: " + sb.toString().trim());
    }
}