import java.lang.reflect.Array;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one argument: the size of the buffer.");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);

            // Allocate a byte array as the buffer
            byte[] buffer = new byte[bufferSize];

            // Print the contents of the buffer (initially filled with zeros)
            for (byte b : buffer) {
                System.out.print(b + " ");
            }
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}