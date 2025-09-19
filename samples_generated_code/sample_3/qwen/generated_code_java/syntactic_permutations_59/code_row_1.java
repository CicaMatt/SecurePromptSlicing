import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size
        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);

        byte valueToSet = 'A';
        for (int i = 0; i < bufferSize; i++) {
            buffer.put(i, valueToSet);
        }

        // Reset position to read from the start of the buffer if needed
        buffer.position(0);

        // Example: Convert buffer content to a string and print it
        String content = StandardCharsets.US_ASCII.decode(buffer).toString();
        System.out.println(content);
    }
}