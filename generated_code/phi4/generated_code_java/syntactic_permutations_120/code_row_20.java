import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class MemoryCopyExample {
    public static void main(String[] args) {
        // Allocate two chunks of memory using ByteBuffer
        int length = 10; // Length of each buffer in bytes

        ByteBuffer firstChunk = ByteBuffer.allocate(length);
        ByteBuffer secondChunk = ByteBuffer.allocate(length);

        // Example data to copy: "HelloWorld"
        String data = "Hello";
        firstChunk.put(data.getBytes(StandardCharsets.UTF_8));

        // Reset position for reading
        firstChunk.flip();

        // Copy contents from the first chunk into the second chunk
        while (firstChunk.hasRemaining()) {
            byte b = firstChunk.get();
            secondChunk.put(b);
        }

        // Reset position of secondChunk to read data
        secondChunk.flip();

        // Print contents of the second chunk
        byte[] copiedData = new byte[secondChunk.remaining()];
        secondChunk.get(copiedData);

        String result = new String(copiedData, StandardCharsets.UTF_8);
        System.out.println(result);
    }
}