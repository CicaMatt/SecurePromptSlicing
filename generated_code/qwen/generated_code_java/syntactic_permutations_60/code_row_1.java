import java.nio.ByteBuffer;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferAllocator <buffer_size>");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            for (int i = 0; i < buffer.capacity(); i++) {
                System.out.print(buffer.get(i) + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.err.println("Invalid buffer size specified.");
            System.exit(1);
        }
    }
}