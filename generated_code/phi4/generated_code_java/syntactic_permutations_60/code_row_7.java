import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferProgram {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferProgram <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

            // Fill the buffer with example data for demonstration purposes
            for (int i = 0; i < bufferSize; i++) {
                buffer.put((byte) i);
            }
            
            buffer.flip(); // Switch to read mode

            byte[] contents = new byte[buffer.remaining()];
            buffer.get(contents);

            System.out.println("Buffer Contents: " + Arrays.toString(contents));
        } catch (NumberFormatException e) {
            System.out.println("Error: Argument must be an integer.");
        }
    }
}