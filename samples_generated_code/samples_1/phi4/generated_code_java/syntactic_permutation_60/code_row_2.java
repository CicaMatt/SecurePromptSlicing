import java.util.Arrays;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferAllocator <bufferSize>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];
            
            System.out.println("Buffer allocated and initialized:");
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.err.println("Error: The argument must be a valid integer.");
            System.exit(1);
        }
    }
}