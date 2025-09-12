import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Please provide a single integer argument specifying the buffer size.");
            System.exit(1);
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill buffer with some data for demonstration purposes
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip(); // Switch to read mode

            System.out.println("Buffer contents:");
            while (buffer.hasRemaining()) {
                byte b = buffer.get();
                System.out.print(b + " ");
            }

        } catch (NumberFormatException e) {
            System.err.println("Argument must be a valid integer.");
            System.exit(1);
        }
    }
}