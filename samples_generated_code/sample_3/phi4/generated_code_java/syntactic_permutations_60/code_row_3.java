import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            if (bufferSize <= 0) {
                throw new IllegalArgumentException("Buffer size must be positive.");
            }

            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with some example data
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip(); // Prepare the buffer for reading

            System.out.print("Buffer contents: ");
            while (buffer.hasRemaining()) {
                System.out.print(buffer.get() + " ");
            }

        } catch (NumberFormatException e) {
            System.out.println("Error: Buffer size must be a valid integer.");
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
}