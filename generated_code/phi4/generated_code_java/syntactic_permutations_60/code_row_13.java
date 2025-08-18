import java.util.Arrays;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <size>");
            return;
        }

        try {
            int size = Integer.parseInt(args[0]);
            byte[] buffer = new byte[size];

            // Print the contents of the buffer
            System.out.println("Buffer contents:");
            System.out.println(Arrays.toString(buffer));
        } catch (NumberFormatException e) {
            System.out.println("Error: Size must be a valid integer.");
        }
    }
}