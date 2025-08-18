import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <buffer_size>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer for buffer size.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        byte[] bytes = new byte[bufferSize];
        buffer.get(bytes);

        String contents = StandardCharsets.UTF_8.decode(java.nio.ByteBuffer.wrap(bytes)).toString();
        System.out.println("Contents of the buffer: " + contents);
    }
}