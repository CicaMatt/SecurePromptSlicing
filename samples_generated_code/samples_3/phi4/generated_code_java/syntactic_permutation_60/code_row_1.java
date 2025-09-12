import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferAllocator {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <size>");
            return;
        }

        try {
            int size = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(size);
            
            // Fill the buffer with some data
            for (int i = 0; i < size; i++) {
                buffer.put((byte) i % 256); // Filling with incremental values
            }
            
            // Print the contents of the buffer as a byte array
            System.out.println(Arrays.toString(buffer.array()));
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for size.");
        }
    }
}