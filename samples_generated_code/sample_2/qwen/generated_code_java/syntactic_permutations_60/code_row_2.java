import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferAllocator <buffer_size>");
            System.exit(1);
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.err.println("Buffer size must be an integer.");
            System.exit(1);
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        for (int i = 0; i < bufferSize; i++) {
            System.out.print(buffer.get(i) & 0xFF); // Print each byte as unsigned int
            if (i < bufferSize - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();
    }
}