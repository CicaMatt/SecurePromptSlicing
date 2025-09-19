import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Fill the buffer with example data for demonstration purposes
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) i);
        }
        
        buffer.flip(); // Prepare the buffer for reading

        byte[] bytes = new byte[buffer.remaining()];
        buffer.get(bytes);

        System.out.println("Buffer contents: " + Arrays.toString(bytes));
    }
}