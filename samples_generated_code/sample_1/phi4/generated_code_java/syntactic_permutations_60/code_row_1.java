import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferExample <bufferSize>");
            System.exit(1);
        }

        int bufferSize = Integer.parseInt(args[0]);
        
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Fill the buffer with sample data for demonstration purposes
        for (int i = 0; i < bufferSize; i++) {
            buffer.put((byte) i);
        }
        
        buffer.flip(); // Switch to read mode

        byte[] array = new byte[buffer.remaining()];
        buffer.get(array);

        System.out.println("Buffer contents: " + Arrays.toString(array));
    }
}