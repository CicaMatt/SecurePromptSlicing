import java.nio.ByteBuffer;
import java.util.Arrays;

public class BufferExample {
    public static void main(String[] args) {
        if (args.length != 1 || !args[0].matches("\\d+")) {
            System.out.println("Usage: java BufferExample <buffer_size>");
            return;
        }

        int bufferSize = Integer.parseInt(args[0]);
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        // Fill the buffer with dummy data for demonstration
        byte[] demoData = new byte[bufferSize];
        Arrays.fill(demoData, (byte) 1); // fill with a constant value

        buffer.put(demoData);
        
        System.out.println("Buffer contents: " + Arrays.toString(buffer.array()));
    }
}