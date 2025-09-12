import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class BufferExample {
    public static void main(String[] args) {
        int bufferSize = 1024; // Example buffer size, can be adjusted as needed

        ByteBuffer buffer = ByteBuffer.allocate(bufferSize);
        
        byte characterA = 'A';
        for (int i = 0; i < bufferSize; i++) {
            buffer.put(i, characterA);
        }

        // Optionally, to print the buffer content
        String result = StandardCharsets.UTF_8.decode(buffer).toString();
        System.out.println(result);
    }
}