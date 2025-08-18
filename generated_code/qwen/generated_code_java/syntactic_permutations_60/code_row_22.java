import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class BufferAllocator {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferAllocator <buffer-size>");
            return;
        }

        int bufferSize;
        try {
            bufferSize = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("Invalid buffer size specified.");
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        byte[] bytes = new byte[buffer.capacity()];
        buffer.get(bytes);

        String content = new String(bytes, StandardCharsets.UTF_8).trim();
        System.out.println("Buffer contents: '" + content + "'");
    }
}