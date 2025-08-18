import java.nio.ByteBuffer;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].matches("\\d+")) {
            System.out.println("Please provide a valid positive integer size for the buffer.");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Fill the buffer with sample data
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) (i % 256));
        }
        
        // Print the contents of the buffer
        buffer.flip(); // Switch to reading mode
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}