import java.nio.ByteBuffer;

public class BufferExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferExample <bufferSize>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("<bufferSize> must be a valid integer.");
            return;
        }

        if (bufferSize <= 0) {
            System.out.println("Buffer size must be greater than zero.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Print the contents of the buffer
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) i);
        }
        
        buffer.flip(); // Prepare buffer to read from the beginning

        System.out.print("Buffer Contents: ");
        while (buffer.hasRemaining()) {
            System.out.print(buffer.get() + " ");
        }
    }
}