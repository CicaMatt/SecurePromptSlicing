import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <buffer_size>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Buffer size must be an integer.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        for (int i = 0; i < bufferSize; i++) {
            System.out.print(buffer.get(i));
        }
    }
}