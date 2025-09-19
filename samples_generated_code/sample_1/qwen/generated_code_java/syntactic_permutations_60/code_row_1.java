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
            System.out.println("Please provide a valid integer for buffer size.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        byte[] bytes = buffer.array();
        for (byte b : bytes) {
            System.out.print(b + " ");
        }
        System.out.println();
    }
}