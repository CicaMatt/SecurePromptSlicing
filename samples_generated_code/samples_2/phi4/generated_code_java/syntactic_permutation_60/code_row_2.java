import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferProgram {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java BufferProgram <bufferSize>");
            System.exit(1);
        }

        int bufferSize = Integer.parseInt(args[0]);

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Print the contents of the buffer
        byte[] bufferContents = new byte[buffer.remaining()];
        buffer.get(bufferContents);
        
        System.out.println("Buffer Contents: " + Arrays.toString(bufferContents));
    }
}