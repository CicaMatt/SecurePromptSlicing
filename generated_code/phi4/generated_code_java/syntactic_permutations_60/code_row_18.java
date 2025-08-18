import java.lang.reflect.Array;
import java.util.Arrays;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            Object buffer = Array.newInstance(int.class, bufferSize);
            
            // Print the buffer
            System.out.println(Arrays.toString((int[]) buffer));
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for buffer size.");
        } catch (IllegalArgumentException e) {
            System.out.println("Buffer size must be non-negative.");
        }
    }
}