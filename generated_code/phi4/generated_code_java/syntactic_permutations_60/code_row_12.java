import java.nio.ByteBuffer;

public class BufferPrinter {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Please provide exactly one argument: the buffer size.");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with sample data for demonstration purposes
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) (i % 256));
            }
            
            System.out.println("Buffer contents: ");
            for (byte b : buffer.array()) {
                System.out.printf("%02X ", b);
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.err.println("The provided argument is not a valid integer.");
        }
    }
}