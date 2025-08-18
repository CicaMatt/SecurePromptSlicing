import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <buffer_size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
            System.out.print(".");
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for the buffer size.");
        }
    }
}