import java.nio.ByteBuffer;
import java.util.Scanner;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferAllocator <size>");
            System.exit(1);
        }

        try {
            int size = Integer.parseInt(args[0]);
            
            ByteBuffer buffer = ByteBuffer.allocate(size);

            // Fill the buffer with some data for demonstration
            for (int i = 0; i < buffer.capacity(); i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip();

            System.out.print("Buffer contents: ");
            while (buffer.hasRemaining()) {
                byte b = buffer.get();
                System.out.print(b + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.err.println("Error: The size must be a valid integer.");
            System.exit(1);
        }
    }
}